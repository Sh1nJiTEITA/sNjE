cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME snje)

project(${PROJECT_NAME})

include_directories(include)
include_directories(shaders)

set(SOURCES 
	src/Shader.cpp
	"src/Camera.cpp"
)


add_executable(${PROJECT_NAME} 
	"main.cpp" 
	${SOURCES} 
	"include/Shader.h"
	"include/LocalException.hpp"
	"include/Camera.h"
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

# CATCH 2
add_subdirectory(external/catch2)
add_executable(tests
	${SOURCES}
	"tests/test.cpp"
	"include/Shader.h" 	
	"include/LocalException.hpp"
	"include/Camera.h"
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE glad)
target_link_libraries(tests PRIVATE glm)
target_link_libraries(tests PRIVATE glfw)


# Shader Files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test.vert
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test.frag
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.vert
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.frag
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)