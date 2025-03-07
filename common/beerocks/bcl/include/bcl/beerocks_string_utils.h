/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _BEEROCKS_STRING_UTILS_H_
#define _BEEROCKS_STRING_UTILS_H_

#include <stdint.h>
#include <string.h>

#include <cstddef>
#include <string>
#include <vector>

namespace beerocks {
class string_utils {
public:
    ///
    /// @brief trim whitespace in place from the head of a string.
    ///
    static void ltrim(std::string &, const std::string &additional_chars = std::string());

    ///
    /// @brief trim whitespace in place from the tail of a string.
    ///
    static void rtrim(std::string &, const std::string &additional_chars = std::string());

    ///
    /// @brief trim whitespace in place from the head and tail of a string.
    ///
    static void trim(std::string &, const std::string &additional_chars = std::string());

    ///
    /// @brief get a head trimmed substring from provided string
    ///
    /// @return string the resulting trimmed substring
    ///
    static std::string ltrimmed_substr(const std::string &);

    ///
    /// @brief get a tail trimmed substring from provided string
    ///
    /// @return string the resulting trimmed substring
    ///
    static std::string rtrimmed_substr(const std::string &);

    ///
    /// @brief get a head and tail trimmed substring from provided string
    ///
    /// @return string the resulting trimmed substring
    ///
    static std::string trimmed_substr(const std::string &);

    ///
    /// @brief check if the provided string is empty
    ///
    /// @return boolean true if the string contains only whitespace characters
    ///
    static bool is_empty(const std::string &);

    ///
    /// @brief get a head and tail trimmed substring from provided string
    ///
    /// @return string representation of the boolean value ["true" | "false"]
    ///
    static std::string bool_str(bool val);

    static std::vector<std::string> str_split(const std::string &s, char delim);

    static bool case_insensitive_compare(const std::string &, const std::string &);

    /**
     * @brief Check is string @a str ends with the string @a suffix.
     * 
     * @param str A string to check if it ends with @a suffix. 
     * @param suffix A suffix to check whether @a str ends with it.
     * @return true if @a str ends with @a suffix, false otherwise.
     */
    static bool endswith(const std::string &str, const std::string &suffix);

#ifndef __GNUC__
#define __builtin_FILE() __FILE__
#define __builtin_LINE() __LINE__
#endif

    static int64_t stoi(const std::string &str, const char *calling_file = __builtin_FILE(),
                        int calling_line = __builtin_LINE());

    /**
     * @brief Convert a hex represented string into characters.
     *
     * @param [in] hex_data Hexadecimal string
     * 
     * @return Container of type T (vector or string) where each cell contains a single character.
     */
    template <class T> static T hex_to_bytes(std::string hex_data)
    {
        T data;

        // Convert the input data from hex string to character
        // sequence and push into T type container
        size_t hex_data_len = hex_data.length();
        for (size_t i = 0; i < hex_data_len; i += 2) {
            auto byte     = hex_data.substr(i, 2);
            auto hex_byte = uint8_t(strtol(byte.c_str(), nullptr, 16));
            data.push_back(hex_byte);
        }

        return data;
    }

    static std::string int_to_hex_string(const unsigned int integer,
                                         const uint8_t number_of_digits);

    /**
     * @brief Convert bytes string to a string, e.g. "7072706c4d657368" -> "prplMesh".
     * 
     * @param byte_string Bytes string.
     * @return std::string Converted string.
     */
    static std::string bytes_string_to_string(const std::string &bytes_string);

    static void copy_string(char *dst, const char *src, size_t dst_len);
};
} // namespace beerocks

#endif //_BEEROCKS_STRING_UTILS_H_
