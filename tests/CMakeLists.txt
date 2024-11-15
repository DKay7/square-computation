enable_testing()

add_executable(
  test_geometry
  test_triangle.cpp
)

target_link_libraries(
  test_geometry
  geometry
  GTest::gtest_main
)

target_include_directories(test_geometry PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(test_geometry) 
