project(bcl VERSION ${prplmesh_VERSION})

# Set the base path for the current module
set(MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

find_package(PythonInterp REQUIRED)
find_package(nl-3 REQUIRED)
find_package(nl-route-3 REQUIRED)

message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

message("${BoldWhite}Preparing ${BoldGreen}${PROJECT_NAME}${BoldWhite} for the ${BoldGreen}${TARGET_PLATFORM}${BoldWhite} platform${ColourReset}")

# Common Sources
file(GLOB_RECURSE bcl_sources ${MODULE_PATH}/source/*.c*)

# Build the library
add_library(${PROJECT_NAME} ${bcl_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${prplmesh_VERSION} SOVERSION ${prplmesh_VERSION_MAJOR})

# Includes
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC nl-3 nl-route-3 tlvf elpp)

install(TARGETS ${PROJECT_NAME} EXPORT bclConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install external header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(EXPORT bclConfig NAMESPACE beerocks:: DESTINATION lib/cmake/beerocks/${PROJECT_NAME})

add_definitions(-DBEEROCKS_VERSION="${prplmesh_VERSION}")

if(BUILD_TESTS)
    set(TEST_PROJECT_NAME ${PROJECT_NAME}_unit_tests)
    set(unit_tests_sources
        ${bcl_sources}
        ${MODULE_PATH}/unit_tests/bridge_state_manager_impl_test.cpp
        ${MODULE_PATH}/unit_tests/buffer_impl_test.cpp
        ${MODULE_PATH}/unit_tests/cmdu_client_impl_test.cpp
        ${MODULE_PATH}/unit_tests/cmdu_parser_stream_impl_test.cpp
        ${MODULE_PATH}/unit_tests/cmdu_serializer_stream_impl_test.cpp
        ${MODULE_PATH}/unit_tests/cmdu_server_impl_test.cpp
        ${MODULE_PATH}/unit_tests/mac_map_test.cpp
        ${MODULE_PATH}/unit_tests/network_utils_test.cpp
        ${MODULE_PATH}/unit_tests/event_loop_impl_test.cpp
        ${MODULE_PATH}/unit_tests/interface_state_manager_impl_test.cpp
        ${MODULE_PATH}/unit_tests/timer_impl_test.cpp
        ${MODULE_PATH}/unit_tests/timer_manager_impl_test.cpp
        ${MODULE_PATH}/unit_tests/transaction_test.cpp
        ${MODULE_PATH}/unit_tests/ucc_parser_stream_impl_test.cpp
        ${MODULE_PATH}/unit_tests/ucc_serializer_stream_impl_test.cpp
        ${MODULE_PATH}/unit_tests/ucc_server_impl_test.cpp
        ${MODULE_PATH}/unit_tests/wireless_utils_test.cpp
        ${MODULE_PATH}/unit_tests/beerocks_utils_test.cpp
        ${MODULE_PATH}/unit_tests/assoc_frame_utils_test.cpp
        ${MODULE_PATH}/unit_tests/beerocks_wifi_channel_test.cpp
    )
    add_executable(${TEST_PROJECT_NAME}
        ${unit_tests_sources}
    )

    if(COVERAGE)
        set_target_properties(${TEST_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "--coverage -fPIC -O0")
        set_target_properties(${TEST_PROJECT_NAME} PROPERTIES LINK_FLAGS "--coverage")
    endif()

    target_include_directories(${TEST_PROJECT_NAME}
        PRIVATE
        ${PLATFORM_INCLUDE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    target_link_libraries(${TEST_PROJECT_NAME} nl-3 nl-route-3 tlvf elpp)
    target_link_libraries(${TEST_PROJECT_NAME} gtest_main gmock)
    install(TARGETS ${TEST_PROJECT_NAME} DESTINATION tests)
    add_test(NAME ${TEST_PROJECT_NAME} COMMAND $<TARGET_FILE:${TEST_PROJECT_NAME}>)
endif()
