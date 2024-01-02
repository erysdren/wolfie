
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
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/sdl2-cmake-modules")

# sdl2
find_package(SDL2 REQUIRED)

# eui
option(EUI_BUILD_EXAMPLES "Build Example Applications" OFF)
option(EUI_INSTALL_TARGET "Enable Install Target" OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/eui)

# tinyfiledialogs
add_library(tinyfiledialogs
	${PROJECT_SOURCE_DIR}/external/tinyfiledialogs/tinyfiledialogs.c)
target_include_directories(tinyfiledialogs PUBLIC
	${PROJECT_SOURCE_DIR}/external/tinyfiledialogs/)

# compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(WOLFIE_COMPILE_OPTIONS -std=c89 -pedantic -Wall -Wextra)
else()
	set(WOLFIE_COMPILE_OPTIONS)
endif()

# compile definitions
set(WOLFIE_COMPILE_DEFINITIONS)

# executable
add_executable(wolfie
	${PROJECT_SOURCE_DIR}/source/main.c
	${PROJECT_SOURCE_DIR}/source/wad.c
	${PROJECT_SOURCE_DIR}/source/wolfie.c)
target_link_libraries(wolfie PUBLIC SDL2::Main eui_sdl2 tinyfiledialogs)
target_compile_definitions(wolfie PUBLIC ${WOLFIE_COMPILE_DEFINITIONS})
target_compile_options(wolfie PUBLIC ${WOLFIE_COMPILE_OPTIONS})
configure_file(${PROJECT_SOURCE_DIR}/data/tiledefs.cfg ${PROJECT_BINARY_DIR}/tiledefs.cfg COPYONLY)
