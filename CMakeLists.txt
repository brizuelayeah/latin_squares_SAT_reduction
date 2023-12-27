#########################
#########################
cmake_minimum_required(VERSION 3.5)
project(PRACTICA2 VERSION 2.2 LANGUAGES CXX)

add_subdirectory(minisat-master)

add_executable(main_practica2 main.cc)

target_link_libraries(main_practica2 libminisat)