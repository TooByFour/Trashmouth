project(Sandbox)

set(SOURCES
    src/main.cpp
    src/AppLayer.cpp
    src/AppLayer.h
)

add_executable(sandbox)
target_sources(sandbox PRIVATE ${SOURCES})
target_link_libraries(sandbox PRIVATE trashmouth)
target_include_directories(sandbox PRIVATE src)
