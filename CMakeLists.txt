cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME snje)

project(${PROJECT_NAME})

include_directories(include)
include_directories(shaders)

set(SOURCES 
	src/Shader.cpp
)


add_executable(${PROJECT_NAME} 
	"main.cpp" 
	${SOURCES} 
	"include/LocalException.hpp"
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

# CATCH 2
add_subdirectory(external/catch2)
add_executable(tests 
	"tests/test.cpp" 
	"include/Shader.h" 
	"src/Shader.cpp" 
	"include/LocalException.hpp"
	"external/glad"
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE glad)
# GLM
add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

# Shader Files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test.vert
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test.frag
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
