/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <bcl/beerocks_string_utils.h>

#include <easylogging++.h>

#include <iomanip>

using namespace beerocks;

static const std::string WHITESPACE_CHARS(" \t\n\r\f\v");

void string_utils::ltrim(std::string &str, const std::string &additional_chars)
{
    str.erase(0, str.find_first_not_of(WHITESPACE_CHARS + additional_chars));
}

void string_utils::rtrim(std::string &str, const std::string &additional_chars)
{
    str.erase(str.find_last_not_of(WHITESPACE_CHARS + additional_chars) + 1);
}

void string_utils::trim(std::string &str, const std::string &additional_chars)
{
    ltrim(str, additional_chars);
    rtrim(str, additional_chars);
}

std::string string_utils::ltrimmed_substr(const std::string &str)
{
    auto start = str.find_first_not_of(WHITESPACE_CHARS);
    if (std::string::npos != start) {
        return str.substr(start);
    }
    return std::string();
}

std::string string_utils::rtrimmed_substr(const std::string &str)
{
    auto end = str.find_last_not_of(WHITESPACE_CHARS);
    if (std::string::npos != end) {
        return str.substr(0, end + 1);
    }
    return std::string();
}

std::string string_utils::trimmed_substr(const std::string &str)
{
    auto start = str.find_first_not_of(WHITESPACE_CHARS);
    auto end   = str.find_last_not_of(WHITESPACE_CHARS);
    if ((std::string::npos != start) && (std::string::npos != end)) {
        return str.substr(start, end - start + 1);
    }
    return std::string();
}

bool string_utils::is_empty(const std::string &str)
{
    return (str.find_first_not_of(WHITESPACE_CHARS) == std::string::npos);
}

std::string string_utils::bool_str(bool val)
{
    return (val) ? std::string("true") : std::string("false");
}

std::vector<std::string> string_utils::str_split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

int64_t string_utils::stoi(const std::string &str, const char *calling_file, int calling_line)
{
    if (str.empty()) {
        auto calling_file_str       = std::string(calling_file);
        const auto caller_file_name = calling_file_str.substr(calling_file_str.rfind('/') + 1);
        LOG(WARNING) << "string_utils::stoi(), string is empty,"
                     << " caller: " << caller_file_name << "[" << calling_line << "]";
        return 0;
    }
    /* There could be a leading space/tab in string
        eg: "1 " or " 1". We need to remove such space/tab and then
        have substring which can be parsed
    */
    std::string trimmed_str = str;
    string_utils::trim(trimmed_str, "");
    if (trimmed_str.find_first_not_of("-0123456789") != std::string::npos) {
        auto calling_file_str       = std::string(calling_file);
        const auto caller_file_name = calling_file_str.substr(calling_file_str.rfind('/') + 1);
        LOG(WARNING) << "string_utils::stoi(), string \"" << str
                     << "\" has illegal characters, caller: " << caller_file_name << "["
                     << calling_line << "]";
        return 0;
    }
    std::stringstream val_s(trimmed_str);
    int64_t val;
    val_s >> val;
    if (val_s.fail()) {
        auto calling_file_str       = std::string(calling_file);
        const auto caller_file_name = calling_file_str.substr(calling_file_str.rfind('/') + 1);
        LOG(WARNING) << "string_utils::stoi(), cannot convert \"" << str
                     << "\" to int64_t, caller: " << caller_file_name << "[" << calling_line << "]";
        return 0;
    }
    return val;
}

std::string string_utils::int_to_hex_string(const unsigned int integer,
                                            const uint8_t number_of_digits)
{
    // 'number_of_digits' represent how much digits the number should have, so the function will
    // pad the number with zeroes from left, if necessary.
    // for example: int_to_hex_string(255, 4) -> "00ff"
    //              int_to_hex_string(255, 1) -> "ff"

    std::stringstream ss_hex_string;

    // convert to hex
    ss_hex_string << std::setw(number_of_digits) << std::setfill('0') << std::hex << integer;

    return ss_hex_string.str();
};

std::string string_utils::bytes_string_to_string(const std::string &bytes_string)
{
    std::string output;
    // Each two characters represent a single byte. Reserve the sufficient amount of memory.
    output.reserve(bytes_string.size() / 2);
    for (size_t char_idx = 0; char_idx < bytes_string.size(); char_idx += 2) {
        output.push_back(
            static_cast<char>(std::strtoul(bytes_string.substr(char_idx, 2).c_str(), nullptr, 16)));
    }
    return output;
}

void string_utils::copy_string(char *dst, const char *src, size_t dst_len)
{
    const char *src_end = std::find(src, src + dst_len, '\0');
    std::copy(src, src_end, dst);
    std::ptrdiff_t src_size = src_end - src;
    std::ptrdiff_t dst_size = dst_len;
    if (src_size < dst_size) {
        dst[src_size] = 0;
    } else {
        dst[dst_size - 1] = 0;
        LOG(ERROR) << "copy_string() overflow, src string:'" << src << "'"
                   << " dst_size=" << dst_size;
    }
}

bool string_utils::case_insensitive_compare(const std::string &lstr, const std::string &rstr)
{
    return lstr.size() == rstr.size() &&
           std::equal(lstr.begin(), lstr.end(), rstr.begin(),
                      [](char a, char b) -> bool { return (tolower(a) == tolower(b)); });
}

bool string_utils::endswith(const std::string &str, const std::string &suffix)
{
    return ((str.size() >= suffix.size()) &&
            (str.compare(str.size() - suffix.size(), suffix.size(), suffix)) == 0);
}
