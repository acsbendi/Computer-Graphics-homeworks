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

target_include_directories(dodge_the_tire PRIVATE "Dodge the tire/include")

target_link_libraries(dodge_the_tire ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "-lglut32 -lopengl32")

project(butterfly)

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(butterfly Butterfly/src/main.cpp Butterfly/include/camera.hpp Butterfly/include/catmullrom.hpp Butterfly/src/butterfly.cpp Butterfly/include/butterfly.hpp Butterfly/src/catmullrom.cpp Butterfly/include/utils.hpp Butterfly/src/camera.cpp Butterfly/include/physics.hpp Butterfly/include/butterfly_body.hpp Butterfly/src/butterfly_body.cpp Butterfly/include/butterfly_wing.hpp Butterfly/src/butterfly_wing.cpp Butterfly/include/opengl.hpp Butterfly/include/cursor.hpp Butterfly/src/physics.cpp Butterfly/include/flowermanager.hpp Butterfly/src/flowermanager.cpp Butterfly/include/flower.hpp Butterfly/src/flower.cpp Butterfly/include/petals.hpp Butterfly/src/petals.cpp Butterfly/include/circle.hpp Butterfly/src/circle.cpp)

list(APPEND CMAKE_PREFIX_PATH "D:/Development/glew-2.1.0")
list(APPEND CMAKE_PREFIX_PATH "D:/Development/freeglut")

find_package(GLEW REQUIRED STATIC)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_libraries(${GLUT_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})

target_include_directories(butterfly PRIVATE "Butterfly/include")

target_link_libraries(butterfly ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

project(fish_tank)

add_executable(fish_tank "Fish Tank/src/main.cpp" "Fish Tank/include/scene.hpp" "Fish Tank/include/utils.hpp" "Fish Tank/src/scene.cpp" "Fish Tank/include/material.hpp" "Fish Tank/include/gold.hpp" "Fish Tank/include/glass.hpp" "Fish Tank/src/gold.cpp" "Fish Tank/src/glass.cpp" "Fish Tank/src/material.cpp" "Fish Tank/include/hit.hpp" "Fish Tank/include/ray.hpp" "Fish Tank/src/ray.cpp" "Fish Tank/include/intersectable.hpp" "Fish Tank/src/intersectable.cpp" "Fish Tank/include/goldenthing.hpp" "Fish Tank/src/goldenthing.cpp" "Fish Tank/include/wall.hpp" "Fish Tank/include/paraboloid.hpp" "Fish Tank/include/room.hpp" "Fish Tank/include/light.hpp" "Fish Tank/include/fisheyecamera.hpp" "Fish Tank/include/camera.hpp" "Fish Tank/include/paraboloidfishtank.hpp" "Fish Tank/include/rectangularfishtank.hpp" "Fish Tank/include/fishtank.hpp" "Fish Tank/include/normalcamera.hpp" "Fish Tank/src/camera.cpp" "Fish Tank/src/room.cpp" "Fish Tank/src/wall.cpp" "Fish Tank/src/fisheyecamera.cpp" "Fish Tank/src/rectangularfishtank.cpp" "Fish Tank/src/paraboloidfishtank.cpp" "Fish Tank/src/paraboloid.cpp" "Fish Tank/src/normalcamera.cpp" "Fish Tank/src/light.cpp")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_libraries(${GLUT_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})

target_include_directories(fish_tank PRIVATE "Fish Tank/include")

target_link_libraries(fish_tank ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})