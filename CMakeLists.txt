cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/FindPackages/)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Engine)
FIND_PACKAGE(Bullet REQUIRED)

file(GLOB MapSrc ${CMAKE_CURRENT_SOURCE_DIR}/Maps/*)

file(COPY ${MapSrc}
        DESTINATION ${CMAKE_BINARY_DIR}/Maps)
include_directories(${BULLET_INCLUDE_DIRS})

add_executable(spacer main.cpp PhysicsBehaviour.cpp PhysicsBehaviour.h RigidBodyComponent.h Map.cpp Map.h)

target_link_libraries(spacer Engine ${BULLET_LIBRARIES})