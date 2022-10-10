CMAKE_MINIMUM_REQUIRED (VERSION 3.6)
Project (openai_cpp VERSION 0.0.1 LANGUAGES CXX)

Include (FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()
set(BUILD_TESTS true)
set(RUN_TESTS_POST_BUILD false)

File (GLOB SRC_FILES
      src/*.cpp
      src/*/*.cpp 
      src/*/*/*.cpp
)

## Fetch external libs

message(STATUS "Fetching OpenAI_Cpp dependencies!")
# RapidJSON
# Just downloaded and embeded header files into project, might make it pull most recent using fetch later

# libcpr
FetchContent_Declare(
      cpr 
      GIT_REPOSITORY "https://github.com/libcpr/cpr.git"
      GIT_TAG "871ed52d350214a034f6ef8a3b8f51c5ce1bd400" # tag version 1.9.0
)
FetchContent_MakeAvailable(cpr)

# fetch googletest
message(STATUS "Fetching googletest")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

## Adding and linking libraries
Add_library (${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 >#/WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

Target_Include_directories (${PROJECT_NAME}
      PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      PRIVATE
)

Target_Link_Libraries (${PROJECT_NAME} 
      PUBLIC
           cpr::cpr
      PRIVATE
           cpr::cpr
)

if(BUILD_TESTS)
    message(STATUS "Building tests!")
    add_subdirectory(test)
endif()
message(STATUS "Done with lib cache generation!")