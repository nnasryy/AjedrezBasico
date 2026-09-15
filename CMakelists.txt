cmake_minimum_required(VERSION 3.16)

project(AjedrezBasico LANGUAGES CXX)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar todos los archivos .cpp del proyecto
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Crear el ejecutable
add_executable(AjedrezBasico ${SOURCES})