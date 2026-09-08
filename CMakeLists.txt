cmake_minimum_required(VERSION 4.3.3)
project(trashmouth VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(trashmouth
    src/main.cpp
)

target_include_directories(trashmouth PRIVATE include)

target_link_libraries(trashmouth PRIVATE
    ${CMAKE_DL_LIBS}
)