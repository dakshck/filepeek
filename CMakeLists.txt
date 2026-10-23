cmake_minimum_required(VERSION 3.20)

project(filepeek)

add_executable(filepeek
	src/main.c
	src/options.c
)

target_include_directories(filepeek PRIVATE 
	include
)
