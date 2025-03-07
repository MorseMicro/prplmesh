# SPDX-License-Identifier: BSD-2-Clause-Patent
#
# SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
#
# This code is subject to the terms of the BSD+Patent license.
# See LICENSE file for more details.

find_library(DWPAL_LIBRARY "libdwpal.so" PATHS ${CMAKE_PREFIX_PATH}/opt/intel/lib)
find_path(DWPAL_INCLUDE_DIRS
    NAMES dwpal.h
    PATH_SUFFIXES wav-dpal
)

find_library(DWPALD_CLIENT_LIBRARY "libdwpald_client.so" PATHS ${CMAKE_PREFIX_PATH}/)
find_path(DWPALD_CLIENT_INCLUDE_DIRS 
    NAMES dwpald_client.h
    PATH_SUFFIXES wav-dpal
)
find_library(WV_CORE_LIBRARY "libwv_core.so" PATHS ${CMAKE_PREFIX_PATH}/)
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(dwpal DEFAULT_MSG
    DWPAL_LIBRARY
    DWPAL_INCLUDE_DIRS
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(dwpald_client DEFAULT_MSG
    DWPALD_CLIENT_LIBRARY
    DWPALD_CLIENT_INCLUDE_DIRS
)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(wv_core DEFAULT_MSG
    WV_CORE_LIBRARY
)
if (dwpal_FOUND)
    add_library(dwpal UNKNOWN IMPORTED)

    # Includes
    set_target_properties(dwpal PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DWPAL_INCLUDE_DIRS}/"
    )

    # Library
    set_target_properties(dwpal PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${DWPAL_LIBRARY}"
    )

endif()
if (dwpald_client_FOUND)
    add_library(dwpald_client UNKNOWN IMPORTED)

    # Includes
    set_target_properties(dwpald_client PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DWPAL_INCLUDE_DIRS}"
    )

    # Library
    set_target_properties(dwpald_client PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${DWPALD_CLIENT_LIBRARY}"
    )

endif()
if (wv_core_FOUND)
    add_library(wv_core UNKNOWN IMPORTED)

    # Library
    set_target_properties(wv_core PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${WV_CORE_LIBRARY}"
    )

endif()
