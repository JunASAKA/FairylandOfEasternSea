cmake_minimum_required(VERSION 3.23) #cmake最低版本
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
project("東方瀛洲誌 ~ Fairyland of Eastern Sea ~") #Project name
add_compile_options(-std=gnu++23 -lglfw3 -lGLEW -lGL -lGLU -lX11 -lpthread -lXrandr -lXi -ldl)#编译选项，非紧急情况不要动。
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
set(SRC_LISTS ${DIR_SRCS})#将源文件整理进一个变量，方便管理。文件之间用半角分号分割。
add_executable(FairylandOfEasternSea ${SRC_LISTS})#同上。
target_link_libraries(FairylandOfEasternSea glfw3 GLEW GL m Xrandr Xi X11 pthread dl Xinerama Xcursor)#链接库，非紧急情况不要动。

