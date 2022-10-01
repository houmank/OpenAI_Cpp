cmake_minimum_required(VERSION 3.6)
project(openai_test)

include (FetchContent)

File(GLOB SRC_FILES
     *.cpp
)

# fetch googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} 
                      PUBLIC 
                          gtest_main
                          openai_cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE openai_cpp)


add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
