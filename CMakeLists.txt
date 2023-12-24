
# cmake settings
cmake_minimum_required(VERSION 3.5)
project(wolfie
	DESCRIPTION "Wolfenstein Interactive Editor"
	HOMEPAGE_URL "https://github.com/erysdren/wolfie/"
	LANGUAGES C
	VERSION 0.0.1
)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# sdl2
find_package(SDL2 REQUIRED)

# compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(WOLFIE_COMPILE_OPTIONS -std=c89 -pedantic -Wall -Wextra)
else()
	set(WOLFIE_COMPILE_OPTIONS)
endif()

# compile definitions
set(WOLFIE_COMPILE_DEFINITIONS EUI_PIXEL_DEPTH=8)

# wolfie executable
add_executable(wolfie
	${PROJECT_SOURCE_DIR}/source/main_sdl2.c
	${PROJECT_SOURCE_DIR}/source/editor.c
	${PROJECT_SOURCE_DIR}/external/eui/source/eui.c
	${PROJECT_SOURCE_DIR}/external/eui/source/eui_sdl2.c)
target_link_libraries(wolfie PUBLIC SDL2::Main)
target_compile_definitions(wolfie PUBLIC ${WOLFIE_COMPILE_DEFINITIONS})
target_compile_options(wolfie PUBLIC ${WOLFIE_COMPILE_OPTIONS})
target_include_directories(wolfie PUBLIC
	${PROJECT_SOURCE_DIR}/external/eui/source)
