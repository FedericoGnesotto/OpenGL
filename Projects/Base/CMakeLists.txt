cmake_minimum_required(VERSION 3.11)

project(Base LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME}
	PRIVATE
        LibOpenGL
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
    LibOpenGL
)