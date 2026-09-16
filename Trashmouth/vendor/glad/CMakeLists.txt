add_library(glad STATIC src/glad.c)

target_include_directories(glad PUBLIC include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})