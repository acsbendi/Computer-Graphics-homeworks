cmake_minimum_required(VERSION 3.9)
project(dodge_the_tire)

set(CMAKE_CXX_STANDARD 17)

add_executable(dodge_the_tire
        "Dodge the tire/src/main.cpp" "Dodge the tire/include/scene.hpp" "Dodge the tire/include/utils.hpp"
        "Dodge the tire/src/scene.cpp" "Dodge the tire/include/object.hpp" "Dodge the tire/include/animatable.hpp"
        "Dodge the tire/src/tire.cpp" "Dodge the tire/include/tire.hpp" "Dodge the tire/include/sphere.hpp"
        "Dodge the tire/include/torus.hpp" "Dodge the tire/include/racetrack.hpp"
        "Dodge the tire/include/light.hpp" "Dodge the tire/include/texture.hpp"
        "Dodge the tire/include/tiretexture.hpp" "Dodge the tire/include/collisiondetector.hpp"
        "Dodge the tire/include/renderstate.hpp" "Dodge the tire/include/shader.hpp"
        "Dodge the tire/include/phongshader.hpp" "Dodge the tire/include/geometry.hpp"
        "Dodge the tire/include/paramsurface.hpp" "Dodge the tire/include/mobius.hpp"
        "Dodge the tire/include/camera.hpp" "Dodge the tire/include/opengl.hpp"
        "Dodge the tire/src/shader.cpp"
        "Dodge the tire/src/phongshader.cpp"
        "Dodge the tire/src/racetrack.cpp"
        "Dodge the tire/src/object.cpp"
        "Dodge the tire/src/skytexture.cpp"
        "Dodge the tire/src/texture.cpp"
        "Dodge the tire/src/sphere.cpp"
        "Dodge the tire/src/roadtexture.cpp"
        "Dodge the tire/src/camera.cpp"
        "Dodge the tire/src/torus.cpp"
        "Dodge the tire/src/paramsurface.cpp"
        "Dodge the tire/src/collisiondetector.cpp"
        "Dodge the tire/src/mobius.cpp"
        "Dodge the tire/src/geometry.cpp")

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

list(APPEND CMAKE_PREFIX_PATH "D:/Development/glew-2.1.0")
list(APPEND CMAKE_PREFIX_PATH "D:/Development/freeglut")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_libraries(${GLUT_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})

include_directories("Dodge the tire/include")

target_link_libraries(dodge_the_tire ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "-lglut32 -lopengl32")
#-Wl,--subsystem,windows