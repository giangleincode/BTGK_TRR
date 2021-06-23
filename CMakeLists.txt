project(graph_jrb)
cmake_minimum_required(VERSION 3.12)

add_subdirectory(graph_jrb)

add_executable(main main.c)

target_link_libraries(main PRIVATE graph)
