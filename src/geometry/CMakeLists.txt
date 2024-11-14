
add_library(geometry Point.cpp Triangle.cpp)

target_include_directories(geometry PUBLIC ${PROJECT_SOURCE_DIR}/../include)
