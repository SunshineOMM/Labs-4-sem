cmake_minimum_required(VERSION 3.5)

project(TMP CXX)

set(CMAKE_CXX_STANDARD 17)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options(/W4 /D_CRT_SECURE_NO_WARNING)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options(-Wail -Wextra -Wpedantic)
endif()

add_subdirectory(lab-1)
add_subdirectory(lab-2)
add_subdirectory(lab-3)

