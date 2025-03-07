project(bwl VERSION ${prplmesh_VERSION})

# Set the base path for the current module
set(MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Common Sources
file(GLOB_RECURSE bwl_common_sources ${MODULE_PATH}/common/*.c*)

# Support more permissive c++ language
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# Default defaults
set(BWL_TYPE "DUMMY" CACHE STRING "BWL type")
set_property(CACHE BWL_TYPE PROPERTY STRINGS "DUMMY" "NL80211" "DWPAL" "DWPALD" "WHM")
add_definitions(-DBEEROCKS_TMP_PATH="${TMP_PATH}")

if (TARGET_PLATFORM STREQUAL "rdkb")

    set(BWL_TYPE "DWPALD")
    # Extra libraries
    list(APPEND BWL_LIBS rt dl)

elseif(TARGET_PLATFORM STREQUAL "openwrt")

    if (TARGET_PLATFORM_TYPE STREQUAL "ugw")
        set(BWL_TYPE "DWPALD")
    else()
        set(BWL_TYPE "NL80211")
    endif()

elseif(TARGET_PLATFORM STREQUAL "MorseMicro")

    set(BWL_TYPE "NL80211")

endif()

if (USE_PRPLMESH_WHM)
    set(BWL_TYPE "WHM")
endif()

set(BWL_TYPE ${BWL_TYPE} CACHE STRING "Which BWL backend to use")

##########################################################################
##########################################################################
##########################################################################
if(BWL_TYPE STREQUAL "DWPALD")
    
    file(GLOB HOSTAPD_SEARCH_PATHS "${PLATFORM_BUILD_DIR}/hostapd*/hostapd-*")
    find_path(HOSTAPD_INCLUDE_DIR NAMES "src/common/wpa_ctrl.h" PATHS ${HOSTAPD_SEARCH_PATHS} NO_CMAKE_FIND_ROOT_PATH)
    set(HOSTAPD_DIR "${HOSTAPD_INCLUDE_DIR}")

    include_directories(
        ${HOSTAPD_DIR}/src/drivers
        ${PLATFORM_BUILD_DIR}/iwlwav-iw-4.14
    )

    file(GLOB bwl_platform_sources
        ${bwl_platform_sources}
        ${MODULE_PATH}/shared/*.c*
        ${MODULE_PATH}/dwpald/*.c*
    )

    find_package(dwpald REQUIRED)
    find_package(nl-3 REQUIRED)
    find_package(nl-genl-3 REQUIRED)
    list(APPEND BWL_LIBS dwpal dwpald_client wv_core nl-3 nl-genl-3)

    # safec library can come from either libsafec or slibc
    find_package(safec QUIET)
    if (safec_FOUND)
        list(APPEND BWL_LIBS safec)
        add_definitions(-DUSE_LIBSAFEC)

        # Signal libsafec that we support the C99 standard
        add_definitions(-DHAVE_C99)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    else()
        find_package(slibc REQUIRED)
        list(APPEND BWL_LIBS slibc)
        add_definitions(-DUSE_SLIBC)
    endif()

elseif(BWL_TYPE STREQUAL "DWPAL")
    
    file(GLOB HOSTAPD_SEARCH_PATHS "${PLATFORM_BUILD_DIR}/hostapd*/hostapd-*")
    find_path(HOSTAPD_INCLUDE_DIR NAMES "src/common/wpa_ctrl.h" PATHS ${HOSTAPD_SEARCH_PATHS} NO_CMAKE_FIND_ROOT_PATH)
    set(HOSTAPD_DIR "${HOSTAPD_INCLUDE_DIR}")

    include_directories(
        ${HOSTAPD_DIR}/src/drivers
        ${PLATFORM_BUILD_DIR}/iwlwav-iw-4.14
    )

    file(GLOB bwl_platform_sources
        ${bwl_platform_sources}
        ${MODULE_PATH}/shared/*.c*
        ${MODULE_PATH}/dwpal/*.c*
    )

    find_package(dwpal REQUIRED)
    find_package(nl-3 REQUIRED)
    find_package(nl-genl-3 REQUIRED)
    list(APPEND BWL_LIBS dwpal nl-3 nl-genl-3)

    # safec library can come from either libsafec or slibc
    find_package(safec QUIET)
    if (safec_FOUND)
        list(APPEND BWL_LIBS safec)
        add_definitions(-DUSE_LIBSAFEC)

        # Signal libsafec that we support the C99 standard
        add_definitions(-DHAVE_C99)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    else()
        find_package(slibc REQUIRED)
        list(APPEND BWL_LIBS slibc)
        add_definitions(-DUSE_SLIBC)
    endif()

elseif(BWL_TYPE STREQUAL "NL80211")

    file(GLOB HOSTAPD_SEARCH_PATHS "${PLATFORM_BUILD_DIR}/hostapd*/hostapd-*")
    find_path(HOSTAPD_INCLUDE_DIR NAMES "src/common/wpa_ctrl.h" PATHS ${HOSTAPD_SEARCH_PATHS} NO_CMAKE_FIND_ROOT_PATH)
    set(HOSTAPD_DIR "${HOSTAPD_INCLUDE_DIR}")

    find_package(nl-genl-3 REQUIRED)
    list(APPEND BWL_LIBS nl-genl-3)

    if(TARGET_PLATFORM STREQUAL "MorseMicro")
    list(APPEND BWL_LIBS wpa_client_s1g)
    endif()
    
    file(GLOB bwl_platform_sources
        ${MODULE_PATH}/shared/*.c*
        ${MODULE_PATH}/nl80211/*.c*

        # WPA Control Interface
        ${HOSTAPD_DIR}/src/common/wpa_ctrl.c
        ${HOSTAPD_DIR}/src/utils/os_unix.c
    )

    # Enable WPA control interface
    add_definitions(
        -DCONFIG_CTRL_IFACE
        -DCONFIG_CTRL_IFACE_UNIX
    )

    # Hostapd/NL80211 include directories
    include_directories(
        ${HOSTAPD_DIR}/src/utils
        ${HOSTAPD_DIR}/src/common
        ${HOSTAPD_DIR}/src/drivers
    )

    # Platform libraries
    link_directories(
        ${PLATFORM_STAGING_DIR}/usr/lib
    )

    list(APPEND BWL_LIBS prplmesh_hostapd)

elseif(BWL_TYPE STREQUAL "DUMMY")

    set(bwl_platform_sources
        ${bwl_platform_sources}
        ${MODULE_PATH}/dummy/nl80211_client_dummy.cpp
        ${MODULE_PATH}/dummy/nl80211_client_factory_dummy.cpp
        ${MODULE_PATH}/dummy/mon_wlan_hal_dummy.cpp
        ${MODULE_PATH}/dummy/ap_wlan_hal_dummy.cpp
        ${MODULE_PATH}/dummy/base_wlan_hal_dummy.cpp
        ${MODULE_PATH}/dummy/sta_wlan_hal_dummy.cpp
    )

elseif(BWL_TYPE STREQUAL "WHM")

    find_package(amxb REQUIRED)
    find_package(amxc REQUIRED)
    find_package(amxd REQUIRED)
    find_package(amxp REQUIRED)
    list(APPEND BWL_LIBS amxb amxc amxd amxp)
    list(APPEND BWL_LIBS wbapi)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WBAPI_SOCK}")

    file(GLOB bwl_platform_sources
        ${bwl_platform_sources}
        ${MODULE_PATH}/whm/*.c*
    )
    
else()

    string(TOLOWER ${BWL_TYPE} BWL_PATH)

    if(EXISTS ${MODULE_PATH}/${BWL_PATH})
        set(bwl_platform_sources
            ${bwl_platform_sources}
	    ${MODULE_PATH}/${BWL_PATH}/mon_wlan_hal_${BWL_PATH}.cpp
	    ${MODULE_PATH}/${BWL_PATH}/ap_wlan_hal_${BWL_PATH}.cpp
	    ${MODULE_PATH}/${BWL_PATH}/base_wlan_hal_${BWL_PATH}.cpp
	    ${MODULE_PATH}/${BWL_PATH}/sta_wlan_hal_${BWL_PATH}.cpp
        )
    else()
        message( FATAL_ERROR "BWL_TYPE not found" )
    endif()

endif()

# Build the library
add_library(${PROJECT_NAME} ${bwl_common_sources} ${bwl_platform_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-z,defs")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${prplmesh_VERSION} SOVERSION ${prplmesh_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} bcl elpp ${BWL_LIBS})
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PLATFORM_INCLUDE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (BUILD_TESTS)
    string(TOLOWER ${BWL_TYPE} BWL_TYPE_LOWERCASE)
    set(TEST_PROJECT_NAME ${PROJECT_NAME}_${BWL_TYPE_LOWERCASE}_unit_tests)
    set(unit_tests_sources
        ${bwl_common_sources} 
        ${bwl_platform_sources} 
        ${MODULE_PATH}/unit_tests/action_frame_parsing_test.cpp
        ${MODULE_PATH}/unit_tests/assoc_frame_body_extract_test.cpp
    )
    if(NOT BWL_TYPE STREQUAL "WHM")
        list(APPEND unit_tests_sources
             ${MODULE_PATH}/unit_tests/nl80211_client_impl_test.cpp
	     ${MODULE_PATH}/unit_tests/nl80211_client_test.cpp
	)
    endif()
    add_executable(${TEST_PROJECT_NAME} 
        ${unit_tests_sources}
    )
    if (COVERAGE)
        set_target_properties(${TEST_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "--coverage -fPIC -O0")
        set_target_properties(${TEST_PROJECT_NAME} PROPERTIES LINK_FLAGS "--coverage")
    endif()
    target_include_directories(${TEST_PROJECT_NAME}
        PRIVATE
            ${PLATFORM_INCLUDE_DIR}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    target_link_libraries(${TEST_PROJECT_NAME} prplmesh_hostapd bcl elpp ${BWL_LIBS})
    target_link_libraries(${TEST_PROJECT_NAME} gtest_main)
    install(TARGETS ${TEST_PROJECT_NAME} DESTINATION tests)
    add_test(NAME ${TEST_PROJECT_NAME} COMMAND $<TARGET_FILE:${TEST_PROJECT_NAME}>)
endif()
