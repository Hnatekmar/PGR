cmake_minimum_required(VERSION 3.8)
project(Engine)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(DevIL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR} ${IL_INCLUDE_DIR})
set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/default.frag
        DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/default.vert
        DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCE_FILES Engine.cpp Engine.h IDrawable.h Shader.cpp Shader.h Buffer.h Exceptions/EngineException.cpp Exceptions/EngineException.h Entity.h EntityManager.cpp EntityManager.h Entity.cpp Primitives/Vertex.h Primitives/Texture.h Primitives/Mesh.h Primitives/Mesh.cpp Primitives/Texture.cpp Primitives/Model.cpp Primitives/Model.h)
add_library(Engine ${SOURCE_FILES})
target_link_libraries(Engine ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES} ${IL_LIBRARIES})
