cmake_minimum_required(VERSION 3.16) #
project(TouhouEishushi) #Project name
add_compile_options(-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)
add_executable(main main.cpp)
target_link_libraries(main glfw3 GL m Xrandr Xi X11 pthread dl Xinerama Xcursor)