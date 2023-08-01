cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME snje)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} "main.cpp")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)


add_subdirectory(external/catch2)
add_executable(tests "tests/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)