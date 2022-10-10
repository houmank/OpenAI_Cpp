cmake_minimum_required(VERSION 3.6)
set(This openai_test)

Set(API_KEY_FILENAME OpenAI_API_SK.txt)

File(GLOB SRC_TESTS
     *.cpp
     */*.cpp
     */*/*.cpp
)

message(STATUS "Googletest executable")
add_executable(${This} ${SRC_TESTS})
target_link_libraries(${This} 
          PUBLIC
               GTest::gtest
               GTest::gtest_main 
               openai_cpp
)
target_include_directories(${This} PRIVATE openai_cpp)

add_test(
    NAME ${This}
    COMMAND ${This}
)

# https://stackoverflow.com/a/72341403
if (WIN32)
    add_custom_command(
        TARGET ${This}
        COMMENT "Copy DLLs"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${This}> $<TARGET_FILE_DIR:${This}>
        COMMAND_EXPAND_LISTS
    )
endif ()

# Copy SK from test source folder to .exe
add_custom_command(
        TARGET ${This}
        COMMENT "Copy Secret Key"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${API_KEY_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}
)

if(RUN_TESTS_POST_BUILD)
    # https://stackoverflow.com/a/32902353
    add_custom_command(
         TARGET ${This}
         COMMENT "Run tests"
         POST_BUILD 
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
         COMMAND ${This}
         #COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${This}$" --output-on-failures
    )
endif()