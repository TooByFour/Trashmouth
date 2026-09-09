project(Trashmouth)

file(GLOB_RECURSE TRASHMOUTH_SOURCES CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE TRASHMOUTH_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb_image)
find_package(OpenGL REQUIRED)

add_library(trashmouth SHARED ${TRASHMOUTH_SOURCES} ${TRASHMOUTH_HEADERS})
target_include_directories(trashmouth PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_precompile_headers(trashmouth PRIVATE src/Trashmouth/tmpch.h)
target_link_libraries(trashmouth PRIVATE stb_image)
target_link_libraries(trashmouth PUBLIC
    glad
    glm:glm
    glfw
    OpenGL::GL)