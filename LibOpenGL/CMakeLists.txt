cmake_minimum_required(VERSION 3.10)

project(LibOpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw-3.3.8)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glm)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad)

set(Resources ${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/Shader.shader
              ${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/InversionShader.shader)

set(Sources 
	# ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FrameBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Bindable.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Camera.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Defines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/FrameBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/IndexBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Shader.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Texture.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Utils.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/VertexArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/VertexBuffer.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/VertexBufferLayout.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/View.h 

    ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb_image.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stb/stb_image.cpp 
    
    ${Resources})

add_library(${PROJECT_NAME} STATIC ${Sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw-3.3.8/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/externals/glm")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)