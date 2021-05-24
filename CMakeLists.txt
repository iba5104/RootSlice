cmake_minimum_required(VERSION 3.17.1)
set(CMAKE_C_COMPILER "gcc-7.1.0")

project (RootSlice)

set (VTK_DIR "C:/VSProjects/VTK-src/VTK-bin")
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

include_directories(include)

file(GLOB SOURCES "code_files/*.cpp")
add_executable(RootSlice MACOSX_BUNDLE ${SOURCES})
target_link_libraries(RootSlice PRIVATE ${VTK_LIBRARIES})


