
add_library(geometry 
    Polygon.cpp Triangle.cpp Vector2.cpp
)

target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include)
