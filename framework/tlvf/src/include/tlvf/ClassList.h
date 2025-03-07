/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _ClassList_H_
#define _ClassList_H_

#include <list>
#include <memory>
#include <tlvf/BaseClass.h>
#include <vector>

class ClassList {

public:
    ClassList() = delete;
    ClassList(uint8_t *buff, size_t buff_len, bool parse = false);
    virtual ~ClassList() = default;

public:
    /**
     * @brief add class on buffer
     *
     * Adds a new class of type T on the ClassList buffer, and
     * finalizes the previous class. Finalize includes endianess conversion,
     * sanity checks, etc, and it is not allowed to update previousely the
     * class after addClass is called for the next class.
     *
     * @tparam T class template type
     * @return std::shared_ptr<T> newly allocated class
     */
    template <class T> std::shared_ptr<T> addClass()
    {
        std::shared_ptr<T> ptr;
        auto prev = m_class_vector.empty() ? nullptr : m_class_vector.back();
        if (!prev) {
            ptr = std::make_shared<T>(m_buff, m_buff_len, m_parse);
        } else {
            // before adding a new class, finalize the previous one
            if (!m_parse) {
                if (!prev->finalize())
                    return nullptr;
            }
            ptr = std::make_shared<T>(prev, m_parse);
        }
        if (!ptr || ptr->isInitialized() == false) {
            return nullptr;
        }

        m_class_vector.push_back(ptr);
        return ptr;
    }

    /**
     * @brief Get the (first) Class object
     *
     * @tparam T class template
     * @return std::shared_ptr<T> to the first object found of type T, nullptr if not found
     */
    template <class T> std::shared_ptr<T> getClass() const { return getClass<T>(0); }

    /**
     * @brief Get a class object of type T in index `idx` in the logical array containing
     *        all classes of type T.
     *
     * @tparam T class template
     * @param idx index in the class T array
     * @return std::shared_ptr<T> to the T class at index `idx` in the class T array
     */
    template <class T> std::shared_ptr<T> getClass(size_t idx) const
    {
        size_t idx_ = 0;
        for (const auto &it : m_class_vector) {
            if (auto c = std::dynamic_pointer_cast<T>(it)) {
                if (idx_++ == idx)
                    return c;
            }
        }
        return nullptr;
    }

    /**
     * @brief Get the list of classes of type T
     *
     * @tparam T class template
     * @return std::list<std::shared_ptr<T>> list of class T pointers
     */
    template <class T> std::list<std::shared_ptr<T>> getClassList() const
    {
        std::list<std::shared_ptr<T>> list;
        for (const auto &it : m_class_vector) {
            if (auto c = std::dynamic_pointer_cast<T>(it)) {
                list.push_back(std::move(c));
            }
        }
        return list;
    }

    /**
     * @brief get previousely added class
     *
     * Get a pointer to the last added class.
     *
     * @return std::shared_ptr<BaseClass> 
     */
    std::shared_ptr<BaseClass> prevClass() const
    {
        return m_class_vector.empty() ? nullptr : m_class_vector.back();
    };

    size_t getMessageLength() const;
    size_t getMessageBuffLength() const { return m_buff_len; };
    uint8_t *getMessageBuff() const { return m_buff; };
    void swap();
    bool is_finalized() const { return m_finalized; };
    bool is_swapped() const { return m_swapped; };
    bool finalize();
    void reset(bool parse);

protected:
    uint8_t *const m_buff;
    size_t m_buff_len;

    bool m_parse     = false;
    bool m_finalized = false;
    bool m_swapped   = false;
    std::vector<std::shared_ptr<BaseClass>> m_class_vector;
};

#endif //_TlvList_H_
