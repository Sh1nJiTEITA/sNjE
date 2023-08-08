cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME snje)

project(${PROJECT_NAME})

include_directories(include)
include_directories(shaders)
include_directories(textures)

# Textures
set(TEXTURE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/textures)
set(TEXTURES
	${TEXTURE_DIR}/container2.png
	${TEXTURE_DIR}/models/cube.dae
)


# Sources
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES 
	${SOURCES_DIR}/Shader.cpp # 1
	${SOURCES_DIR}/Camera.cpp # 2
	${SOURCES_DIR}/snjVertex.cpp # 3
	${SOURCES_DIR}/snjMesh.cpp # 3
)

# Includes
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDES
	${INCLUDE_DIR}/LocalException.hpp
	${INCLUDE_DIR}/stb_image.h

	${INCLUDE_DIR}/Shader.h # 1
	${INCLUDE_DIR}/Camera.h # 2
	${INCLUDE_DIR}/snjVertex.h # 2
	${INCLUDE_DIR}/snjMesh.h # 2
)



add_executable(${PROJECT_NAME} 
	"main.cpp" 
	"main.h"
	${SOURCES}
	${TEXTURES}
	${INCLUDES}
)

# GLFW LIBRARY
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLAD LIBRARY
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

# GLM
add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)


# Assimp
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)


add_subdirectory(external/assimp)
target_link_libraries(${PROJECT_NAME} assimp)


# CATCH 2
add_subdirectory(external/catch2)
add_executable(tests
	"tests/test.cpp"
	"tests/model_test.cpp"
	"tests/mesh_test.cpp"

	${SOURCES}
	${INCLUDES}
	${TEXTURES}
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE glad)
target_link_libraries(tests PRIVATE glm)
target_link_libraries(tests PRIVATE glfw)
target_link_libraries(tests PRIVATE assimp)



# Shader Files
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/std_object.vert
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/std_object.frag
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.vert
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.frag
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/models/cube.obj
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
