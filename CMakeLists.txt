cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME snje)

project(${PROJECT_NAME})

include_directories(include)
include_directories(shaders)
#include_directories(textures)




# Sources
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES 
	${SOURCES_DIR}/Shader.cpp					# 1
	${SOURCES_DIR}/Camera.cpp					# 2
	${SOURCES_DIR}/snjVertex.cpp				# 3
	${SOURCES_DIR}/snjMesh.cpp					# 4
	${SOURCES_DIR}/snjModel.cpp					# 5
	${SOURCES_DIR}/snjLightSourceModel.cpp		# 6
	${SOURCES_DIR}/snjLightsHandler.cpp			# 7
)

# Includes
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDES
	${INCLUDE_DIR}/LocalException.hpp
	${INCLUDE_DIR}/stb_image.h

	${INCLUDE_DIR}/Shader.h						# 1
	${INCLUDE_DIR}/Camera.h						# 2
	${INCLUDE_DIR}/snjVertex.h					# 3
	${INCLUDE_DIR}/snjMesh.h					# 4
	${INCLUDE_DIR}/snjModel.h					# 5
	${INCLUDE_DIR}/snjLightSourceModel.h		# 6
	${INCLUDE_DIR}/snjLightsHandler.h			# 7
)




add_executable(${PROJECT_NAME} 
	"main.cpp" 
	"main.h"
	${SOURCES}
	${INCLUDES}
)


# Textures
add_custom_target(COPY_TEXTURES ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures ${CMAKE_BINARY_DIR}/textures
    DEPENDS # Добавьте зависимости, если необходимо
)

add_dependencies(${PROJECT_NAME} COPY_TEXTURES)



# Shaders

file(GLOB SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*)
foreach(shaderi ${SHADERS})
configure_file(${shaderi} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()





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
	#"tests/model_test.cpp"
	"tests/mesh_test.cpp"

	${SOURCES}
	${INCLUDES}
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE glad)
target_link_libraries(tests PRIVATE glm)
target_link_libraries(tests PRIVATE glfw)
target_link_libraries(tests PRIVATE assimp)

add_dependencies(tests COPY_TEXTURES)


# Shader Files
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/std_object.vert
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/std_object.frag
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)



#FILE(
	#COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
	#DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#)

#file(
	#COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures/models/test
	#DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.vert
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/lamp.frag
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test_shader.vert
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/test_shader.frag
#    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)






#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/models/cube.obj
    #${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/models/something.obj
    #${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/models/FinalBaseMesh.obj
    #${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


