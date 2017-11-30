cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/FindPackages/)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Engine)
FIND_PACKAGE(Bullet REQUIRED)

include_directories(${BULLET_INCLUDE_DIRS})

add_executable(spacer main.cpp PhysicsBehaviour.cpp PhysicsBehaviour.h)

target_link_libraries(spacer Engine ${BULLET_LIBRARIES})