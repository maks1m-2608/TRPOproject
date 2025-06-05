cmake_minimum_required(VERSION 3.11)

project(MapProject)

set(CMAKE_CXX_STANDARD 17)

# Создаем исполняемый файл
add_executable(map
    main.cpp
    interface.h
    interface.cpp
    my_map.h
    my_map.cpp
)