###############################

# cmake_minimum_required(VERSION 3.10)
# project(ForestFireSim)

# set(CMAKE_CXX_STANDARD 17)
# find_package(OpenGL REQUIRED)
# include(FetchContent)

# FetchContent_Declare(
#   glfw
#   GIT_REPOSITORY https://github.com/glfw/glfw.git
#   GIT_TAG latest
# )
# FetchContent_MakeAvailable(glfw)

# add_library(glad STATIC libs/glad/src/glad.c)
# target_include_directories(glad PUBLIC libs/glad/include)

# add_executable(${PROJECT_NAME} src/main.cpp)

# target_link_libraries(${PROJECT_NAME}
#     PRIVATE glfw glad OpenGL::GL ${CMAKE_DL_LIBS}
# )

#################################

cmake_minimum_required(VERSION 3.10)
project(ForestFireSim)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
include(FetchContent)

# === GLFW Fallback ===
set(USE_LOCAL_GLFW OFF)
if(EXISTS "${CMAKE_SOURCE_DIR}/lib/libglfw3.a" OR EXISTS "${CMAKE_SOURCE_DIR}/lib/glfw3.lib")
    set(USE_LOCAL_GLFW, ON)
endif()

if(USE_LOCAL_GLFW)
    message(STATUS "Using local static GLFW from /lib")
    include_directories(include)  # for GLFW/glfw3.h
    link_directories(${CMAKE_SOURCE_DIR}/lib)
else()
    message(STATUS "Using FetchContent to fetch GLFW")
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw.git
      GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)
endif()

# === GLAD ===
add_library(glad STATIC libs/glad/src/glad.c "config/fileroutes.hpp")
target_include_directories(glad PUBLIC libs/glad/include)

# === Exe ===
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Surface.cpp
    src/Cell.cpp
    algorithms/Rothermel.cpp
 "config/fileroutes.hpp")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# === Linking ===
if(USE_LOCAL_GLFW)
    if(MSVC)
        target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 glad opengl32 gdi32)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE libglfw3.a glad opengl32 gdi32)
    endif()
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad OpenGL::GL ${CMAKE_DL_LIBS})
endif()
