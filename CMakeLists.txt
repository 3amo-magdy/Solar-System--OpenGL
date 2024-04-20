cmake_minimum_required(VERSION 3.24)
project(GL_SolarSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(GL_SolarSystem
        main.cpp
        CosmicSphere.cpp
        vec3.h vec3.cpp
        camera.h camera.cpp)

#add_subdirectory(FreeImage)

#link_directories(
#  libraries/lib
#)

# Create a variable to store the source directory
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}")

# Create a variable to store the destination directory
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}")

# Specify the file globbing pattern for DLL files
file(GLOB DLL_FILES "${SOURCE_DIR}/*.dll")
file(GLOB EXE_FILES "${SOURCE_DIR}/*.exe")

# Copy DLL files to the destination directory during the build process
file(COPY ${DLL_FILES} DESTINATION ${DESTINATION_DIR})
# Copy EXE files to the destination directory during the build process
file(COPY ${EXE_FILES} DESTINATION ${DESTINATION_DIR})
# Copy textures to the destination directory during the build process
file(COPY ${SOURCE_DIR}/textures DESTINATION ${DESTINATION_DIR})
# link FreeImage
find_library(FI FreeImage HINTS ${SOURCE_DIR}/FreeImage)
find_library(Glew32 FreeImage HINTS ${SOURCE_DIR}/libraries/lib)

target_link_libraries(GL_SolarSystem PUBLIC ${FI} ${Glew32} ${SOURCE_DIR}/libraries/lib/libfreeglut_static.a ${SOURCE_DIR}/libraries/lib/libfreeglut.a -lopengl32 -lfreeglut -lglu32)
