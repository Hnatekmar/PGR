cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/FindPackages/)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Engine)

add_executable(spacer main.cpp)

target_link_libraries(spacer Engine)