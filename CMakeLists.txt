
# cmake settings
cmake_minimum_required(VERSION 3.5)
project(wolfie
	DESCRIPTION "Wolfenstein Interactive Editor"
	HOMEPAGE_URL "https://github.com/erysdren/wolfie/"
	LANGUAGES CXX
	VERSION 0.0.1
)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/sdl2-cmake-modules")

# get sdl2
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# pedantic compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	list(APPEND WOLFIE_COMPILE_OPTIONS -pedantic -Wall -Wextra)
endif()

# imgui
add_library(imgui
	${PROJECT_SOURCE_DIR}/external/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
	${PROJECT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
	${PROJECT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends/)

add_library(imgui_sdl2_opengl3
	${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_sdl2.cpp
	${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp)
target_link_libraries(imgui_sdl2_opengl3 PUBLIC SDL2::Main OpenGL::OpenGL imgui)

# executable
add_executable(wolfie
	${PROJECT_SOURCE_DIR}/source/main.cpp)
target_link_libraries(wolfie PRIVATE imgui_sdl2_opengl3)
target_compile_definitions(wolfie PRIVATE ${WOLFIE_COMPILE_DEFINITIONS})
target_compile_options(wolfie PRIVATE ${WOLFIE_COMPILE_OPTIONS})
