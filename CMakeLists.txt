cmake_minimum_required(VERSION 3.10)
project(TrainingExersise)

set(CMAKE_CXX_STANDARD 17)

# External dependencies (linked with FetchContent)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
  )
FetchContent_MakeAvailable(googletest)

add_compile_definitions("TNG_DATA_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/data/\"")

add_compile_options(-Werror=sign-compare)
add_compile_options(-fPIC)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tst)

