project(Sandbox)

set(SOURCES
    src/main.cpp
    src/AppLayer.cpp
    src/AppLayer.h
)

add_executable(sandbox src/main.cpp)
target_sources(sandbox PRIVATE ${SOURCES})

target_link_libraries(sandbox PRIVATE trashmouth)
