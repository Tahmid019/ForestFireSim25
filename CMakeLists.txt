cmake_minimum_required(VERSION 3.10)
project(ForestFireSim)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw glad OpenGL::GL ${CMAKE_DL_LIBS}
)
