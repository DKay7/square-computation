cmake_minimum_required(VERSION 3.10)
project(SquareComputation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0074 NEW)

find_package(OpenMP REQUIRED)
if(NOT OpenMP_CXX_FOUND)
	message(SEND_ERROR "Failed to find OpenMP.")
	return()
else()
	include_directories(${OpenMP_INCLUDE_DIRS})
    message("OpenMP FOUND dir is ${OpenMP_INCLUDE_DIRS}.")
endif()
set(CMAKE_CXX_FLAGS "-fopenmp")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(tests)
