cmake_minimum_required(VERSION 3.10)
project(BadBoggleSolver)

set(CMAKE_CXX_STANDARD 17)


## Frame pointers
set(FRAME_PTR_FLAG_YES "-fno-omit-frame-pointer")
## Frame pointers removal
set(FRAME_PTR_FLAG_NO "-fomit-frame-pointer")

option(ADD_FRAME_PTR "Enable tests" ON)
if (${ADD_FRAME_PTR})
  message(STATUS "adding in frame pointers")
  list(APPEND CMAKE_CXX_FLAGS ${FRAME_PTR_FLAG_YES})
else()
  message(STATUS "removing frame pointers")
  list(APPEND CMAKE_CXX_FLAGS ${FRAME_PTR_FLAG_NO})
endif()

add_compile_options(-Werror=sign-compare)
add_compile_options(-fPIC)

# Make data accessible in build
add_custom_target(copy-data-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)
# Make data accessible in install path
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/words_reduced.txt" DESTINATION data)

include_directories(src)
add_subdirectory(src)

option(BUILD_DDPROF_TESTING "Enable tests" OFF)
if (${BUILD_DDPROF_TESTING})
  add_subdirectory(tst)
endif()
