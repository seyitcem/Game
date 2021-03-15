cmake_minimum_required(VERSION 3.16.3)

project(Test)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/main.cpp
		${PROJECT_SOURCE_DIR}/MD5.cpp
		${PROJECT_SOURCE_DIR}/String.cpp
		${PROJECT_SOURCE_DIR}/Console.cpp
		${PROJECT_SOURCE_DIR}/CryptoCurrency.cpp
		${PROJECT_SOURCE_DIR}/Player.cpp
)
set(PROJECT_HEADERS
        ${PROJECT_INCLUDE_DIR}/main.hpp
		${PROJECT_INCLUDE_DIR}/MD5.hpp
		${PROJECT_INCLUDE_DIR}/String.hpp
		${PROJECT_INCLUDE_DIR}/Console.hpp
		${PROJECT_INCLUDE_DIR}/CryptoCurrency.hpp
		${PROJECT_INCLUDE_DIR}/Player.hpp
)
include_directories(
        ${PROJECT_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME})
