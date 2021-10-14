cmake_minimum_required(VERSION 3.10)
project(BadBoggleSolver)

set(CMAKE_CXX_STANDARD 11)

add_compile_definitions("TNG_DATA_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/data/\"")

add_compile_options(-Werror=sign-compare)
add_compile_options(-fPIC)

include_directories(src)
add_subdirectory(src)

option(BUILD_DDPROF_TESTING "Enable tests" OFF)
if (${BUILD_DDPROF_TESTING})
  add_subdirectory(tst)
endif()
