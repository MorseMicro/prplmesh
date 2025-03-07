#include "bpl_uci.h"

#include <bcl/beerocks_string_utils.h>
#include <mapf/common/logger.h>

extern "C" {
#include <uci.h>
}

namespace beerocks {
namespace bpl {

constexpr ssize_t MAX_UCI_BUF_LEN  = 64;
constexpr char package_path[]      = "%s";
constexpr char section_path[]      = "%s.%s";
constexpr char section_type_path[] = "%s.%s=%s";
constexpr char option_path[]       = "%s.%s.%s";
constexpr char option_value_path[] = "%s.%s.%s=%s";

std::string uci_get_error(uci_context *ctx)
{
    char *err_buf = nullptr;
    uci_get_errorstr(ctx, &err_buf, "");
    return std::string(err_buf == nullptr ? "" : err_buf);
}

std::shared_ptr<uci_context> alloc_context()
{
    auto ctx = std::shared_ptr<uci_context>(uci_alloc_context(), [](uci_context *ctx) {
        if (ctx) {
            uci_free_context(ctx);
        }
    });

    LOG_IF(!ctx, ERROR) << "Failed allocating UCI context!";
    return ctx;
}

bool uci_section_exists(const std::string &package_name, const std::string &section_type,
                        const std::string &section_name)
{
    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the package we wish to lookup
    if (snprintf(path, MAX_UCI_BUF_LEN, package_path, package_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_package *pkg = uci_lookup_package(ctx.get(), path);
    if (!pkg) {
        // Try and load the package file, in case it wasn't loaded before
        uci_load(ctx.get(), path, &pkg);
        if (!pkg) {
            LOG(ERROR) << "uci lookup package failed!" << std::endl << uci_get_error(ctx.get());
            return false;
        }
    }

    bool section_found = false;
    // Loop through all sections
    uci_section *sec = nullptr;
    uci_element *elm = nullptr;
    uci_foreach_element(&pkg->sections, elm)
    {
        sec = uci_to_section(elm);
        // uci enforces sections must have unique name
        if (section_name.compare(sec->e.name) == 0) {
            LOG(TRACE) << "Found section: " << sec->type << "(" << sec->e.name << ")";
            section_found = true;
            break;
        }
    }

    if (!section_found) {
        LOG(DEBUG) << "No matching section found for " << section_name;
        return false;
    }

    // If the section_type is empty all matching sections are a valid match
    if (!section_type.empty() && section_type.compare(sec->type) != 0) {
        LOG(DEBUG) << "Section with matching name found, but types don't match" << std::endl
                   << "Searched type: " << section_type << ", Found type: " << sec->type;
        return false;
    }

    return true;
}

bool uci_find_section_by_option(const std::string &package_name, const std::string &section_type,
                                const std::string &option_name, const std::string &option_value,
                                std::string &section_name)
{
    LOG(TRACE) << "uci_find_section_by_option() " << package_name << ".(" << section_type
               << ") with " << option_name << " = " << option_value;

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char pkg_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the package we wish to lookup
    int nchars = snprintf(pkg_path, MAX_UCI_BUF_LEN, package_path, package_name.c_str());
    if ((nchars < 0) || (static_cast<size_t>(nchars) >= MAX_UCI_BUF_LEN)) {
        LOG(ERROR) << "Failed to compose path, nchars = " << nchars;
        return false;
    }

    uci_ptr pkg_ptr;
    // Initialize package pointer from path & validate package existence
    if (uci_lookup_ptr(ctx.get(), &pkg_ptr, pkg_path, true) != UCI_OK || !pkg_ptr.p) {
        LOG(ERROR) << "UCI lookup failed for path: " << pkg_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    // Loop through all sections in the package until a section with given type and option with
    // name=value is found
    uci_package *pkg = pkg_ptr.p;
    uci_element *e   = nullptr;
    uci_foreach_element(&pkg->sections, e)
    {
        uci_section *sec = uci_to_section(e);

        if (section_type.compare(sec->type) != 0) {
            continue;
        }

        // Iterate over all the options in current section
        uci_element *n = nullptr;
        uci_foreach_element(&sec->options, n)
        {
            uci_option *opt = uci_to_option(n);

            if (option_name.compare(opt->e.name) != 0) {
                continue;
            }

            if (opt->type != UCI_TYPE_STRING) {
                continue;
            }

            if (option_value.compare(opt->v.string) != 0) {
                continue;
            }

            // We have reached the specified section
            section_name = sec->e.name;
            return true;
        }
    }

    // Section not found but no error either
    section_name = "";
    return true;
}

bool uci_add_section(const std::string &package_name, const std::string &section_type,
                     const std::string &section_name, bool commit_changes)
{
    //package_name.(section_type)section_name
    LOG(TRACE) << "uci_add_section() " << package_name << ".(" << section_type << ")"
               << section_name;

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char sec_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the section we wish to lookup
    if (snprintf(sec_path, MAX_UCI_BUF_LEN, section_type_path, package_name.c_str(),
                 section_name.c_str(), section_type.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr sec_ptr;
    // Initialize section pointer from path.
    if (uci_lookup_ptr(ctx.get(), &sec_ptr, sec_path, true) != UCI_OK) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << sec_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    // Check if section already exists
    if (sec_ptr.s) {
        LOG(ERROR) << "Section already exists!";
        return false;
    }

    // Add a new named section.
    if (uci_set(ctx.get(), &sec_ptr) != UCI_OK) {
        LOG(ERROR) << "Failed to add new section";
        return false;
    }

    // Create delta from changes, this does not change the persistent file.
    if (uci_save(ctx.get(), sec_ptr.p) != UCI_OK) {
        LOG(ERROR) << "Failed to save changes!" << std::endl << uci_get_error(ctx.get());
        return false;
    }

    if (commit_changes) {
        return uci_commit_changes(package_name);
    }

    return true;
}

bool uci_set_section(const std::string &package_name, const std::string &section_type,
                     const std::string &section_name, const OptionsUnorderedMap &options,
                     bool commit_changes)
{

    //package_name.(section_type)section_name
    LOG(TRACE) << "uci_set_section() " << package_name << ".(" << section_type << ")"
               << section_name << " with options count:" << options.size();

    LOG_IF(options.size() > 0, DEBUG)
        << "First option: " << options.begin()->first << " value: " << options.begin()->second;

    if (!uci_section_exists(package_name, section_type, section_name)) {
        LOG(ERROR) << "section " << section_name << " of type " << section_type
                   << " was not found!";
        return false;
    }

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    for (auto &option : options) {
        char opt_path[MAX_UCI_BUF_LEN] = {0};
        // Generate a uci path to the option we wish to set
        if (snprintf(opt_path, MAX_UCI_BUF_LEN, option_path, package_name.c_str(),
                     section_name.c_str(), option.first.c_str()) <= 0) {
            LOG(ERROR) << "Failed to compose path";
            return false;
        }

        uci_ptr opt_ptr;
        // Initialize option pointer from path.
        if (uci_lookup_ptr(ctx.get(), &opt_ptr, opt_path, true) != UCI_OK) {
            LOG(ERROR) << "UCI failed to lookup ptr for path: " << opt_path << std::endl
                       << uci_get_error(ctx.get());
            return false;
        }
        // Set the value of option in uci_ptr
        // when using uci_set, it will store the change in the context
        auto value_ptr = strdup(option.second.c_str());
        if (!value_ptr) {
            LOG(ERROR) << "Failed to duplicate value buffer";
            return false;
        }
        opt_ptr.value = value_ptr;

        /*
            If the value is set to empty the option will be removed
            If the option does not exist it will be created
            If the option does exist the value will be overridden
        */
        if (uci_set(ctx.get(), &opt_ptr) != UCI_OK) {
            LOG(ERROR) << "Failed to set option " << option.first << std::endl
                       << uci_get_error(ctx.get());
            return false;
        }

        // Create delta from changes in the coxtext, this does not change the persistent file.
        if (uci_save(ctx.get(), opt_ptr.p) != UCI_OK) {
            LOG(ERROR) << "Failed to save changes!" << std::endl << uci_get_error(ctx.get());
            return false;
        }
    }

    if (commit_changes) {
        return uci_commit_changes(package_name);
    }

    return true;
}

bool uci_get_section(const std::string &package_name, const std::string &section_type,
                     const std::string &section_name, OptionsUnorderedMap &options)
{
    //package_name.(section_type)section_name
    LOG(TRACE) << "uci_get_section() " << package_name << ".(" << section_type << ")"
               << section_name;

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char sec_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the section we wish to lookup
    if (snprintf(sec_path, MAX_UCI_BUF_LEN, section_path, package_name.c_str(),
                 section_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr sec_ptr;
    // Initialize section pointer from path & validate section existace
    if (uci_lookup_ptr(ctx.get(), &sec_ptr, sec_path, true) != UCI_OK || !sec_ptr.s) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << sec_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    // Loop through the option within the found section
    uci_element *elm = nullptr;
    uci_foreach_element(&sec_ptr.s->options, elm)
    {
        uci_option *opt = uci_to_option(elm);
        // Only type UCI_TYPE_STRING is supported
        if (opt->type == UCI_TYPE_STRING) {
            options[std::string(opt->e.name)] = opt->v.string;
        }
    }

    return true;
}

bool uci_get_section_type(const std::string &package_name, const std::string &section_name,
                          std::string &section_type)
{
    //package_name.section_name
    LOG(TRACE) << "uci_get_section_type() " << package_name << "." << section_name;

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char sec_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the section we wish to lookup
    if (snprintf(sec_path, MAX_UCI_BUF_LEN, section_path, package_name.c_str(),
                 section_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr sec_ptr;
    // Initialize section pointer from path & validate section existace
    if (uci_lookup_ptr(ctx.get(), &sec_ptr, sec_path, true) != UCI_OK || !sec_ptr.s) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << sec_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    section_type = sec_ptr.s->type;
    return true;
}

bool uci_get_option(const std::string &package_name, const std::string &section_type,
                    const std::string &section_name, const std::string &option_name,
                    std::string &option_value)
{
    //package_name.(section_type)section_name.option_name
    LOG(TRACE) << "uci_get_param() " << package_name << ".(" << section_type << ")" << section_name
               << "." << option_name;

    if (!uci_section_exists(package_name, section_type, section_name)) {
        LOG(ERROR) << "section " << section_name << " of type " << section_type
                   << " was not found!";
        return false;
    }

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char opt_path[MAX_UCI_BUF_LEN]         = {0};
    char copy_of_opt_path[MAX_UCI_BUF_LEN] = {0}; // original opt_path is changed in the following
    // Generate a uci path to the option we wish to lookup
    if (snprintf(opt_path, MAX_UCI_BUF_LEN, option_path, package_name.c_str(), section_name.c_str(),
                 option_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }
    beerocks::string_utils::copy_string(copy_of_opt_path, opt_path, MAX_UCI_BUF_LEN);

    uci_ptr opt_ptr;
    // Initialize option pointer from path & validate option existace
    if (uci_lookup_ptr(ctx.get(), &opt_ptr, opt_path, true) != UCI_OK || !opt_ptr.o) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << copy_of_opt_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    option_value = opt_ptr.o->v.string;
    return true;
}

bool uci_delete_section(const std::string &package_name, const std::string &section_type,
                        const std::string &section_name, bool commit_changes)
{
    //package_name.(section_type)section_name
    LOG(TRACE) << "uci_delete_section() " << package_name << ".(" << section_type << ")"
               << section_name;

    // Verify requested section exists
    if (!uci_section_exists(package_name, section_type, section_name)) {
        LOG(ERROR) << "section " << section_name << " of type " << section_type
                   << " was not found!";
        return false;
    }

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char sec_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the section we wish to lookup
    if (snprintf(sec_path, MAX_UCI_BUF_LEN, section_path, package_name.c_str(),
                 section_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr sec_ptr;
    // Initialize section pointer from path & validate section existace
    if (uci_lookup_ptr(ctx.get(), &sec_ptr, sec_path, true) != UCI_OK || !sec_ptr.s) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << sec_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    if (uci_delete(ctx.get(), &sec_ptr) != UCI_OK) {
        LOG(ERROR) << "UCI failed to delete ptr: " << sec_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    // Create delta from changes, this does not change the persistent file.
    if (uci_save(ctx.get(), sec_ptr.p) != UCI_OK) {
        LOG(ERROR) << "Failed to save changes!" << std::endl << uci_get_error(ctx.get());
        return false;
    }

    if (commit_changes) {
        return uci_commit_changes(package_name);
    }

    return true;
}

bool uci_get_all_sections(const std::string &package_name, const std::string &section_type,
                          std::vector<std::string> &sections)
{
    //package_name.(section_type)
    LOG(TRACE) << "uci_get_all_sections() " << package_name << ".(" << section_type << ")";

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    char pkg_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the package we wish to lookup
    if (snprintf(pkg_path, MAX_UCI_BUF_LEN, package_path, package_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr pkg_ptr;
    // Initialize package pointer from path & validate package existace
    if (uci_lookup_ptr(ctx.get(), &pkg_ptr, pkg_path, true) != UCI_OK || !pkg_ptr.p) {
        LOG(ERROR) << "UCI lookup failed for path: " << pkg_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }

    // Loop through all sections
    uci_element *elm = nullptr;
    uci_foreach_element(&pkg_ptr.p->sections, elm)
    {
        uci_section *sec = uci_to_section(elm);
        // If section type matches add to result
        if (section_type.empty() || section_type.compare(sec->type) == 0) {
            sections.emplace_back(sec->e.name);
        }
    }
    return true;
}

bool uci_commit_changes(const std::string &package_name)
{
    LOG(TRACE) << "uci_commit_changes() ";

    auto ctx = alloc_context();
    if (!ctx) {
        return false;
    }

    // To save the changes made we need to call "uci_commit" with the package
    // Loading a uci_ptr will also load the changes saved in the context's delta
    char pkg_path[MAX_UCI_BUF_LEN] = {0};
    // Generate a uci path to the package we wish to lookup
    if (snprintf(pkg_path, MAX_UCI_BUF_LEN, package_path, package_name.c_str()) <= 0) {
        LOG(ERROR) << "Failed to compose path";
        return false;
    }

    uci_ptr pkg_ptr;
    // Initialize package pointer from path & validate package existace.
    if (uci_lookup_ptr(ctx.get(), &pkg_ptr, pkg_path, true) != UCI_OK || !pkg_ptr.p) {
        LOG(ERROR) << "UCI failed to lookup ptr for path: " << pkg_path << std::endl
                   << uci_get_error(ctx.get());
        return false;
    }
    // Commit changes to file
    if (uci_commit(ctx.get(), &pkg_ptr.p, false) != UCI_OK) {
        LOG(ERROR) << "Failed to commit changes!" << std::endl << uci_get_error(ctx.get());
        return false;
    }

    return true;
}

} // namespace bpl
} // namespace beerocks
