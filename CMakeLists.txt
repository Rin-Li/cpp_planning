cmake_minimum_required(VERSION 3.10)
project(cpp_planning)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})

set(UTIL_SOURCES
    geometry/geometry.cpp
    collision/gjk.cpp
)

set(RRT_SOURCES
    RRT/rrt.cpp
    RRT/rrt_star.cpp
    RRT/rrt_star_bicycle.cpp
)

add_executable(rrt_star_exec
    main_rrt_star.cpp
    ${UTIL_SOURCES}
    ${RRT_SOURCES}
)

add_executable(simple_car_exec
    main_simple_car.cpp
    ${UTIL_SOURCES}
    ${RRT_SOURCES}
)

add_executable(collsion_test_exec
    main_collision_test.cpp
    ${UTIL_SOURCES}
    ${RRT_SOURCES}
)
