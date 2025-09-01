cmake_minimum_required(VERSION 3.10)
project(ForestFireSim)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
include(FetchContent)

# === GLFW Fallback ===
set(USE_LOCAL_GLFW OFF)
if(EXISTS "${CMAKE_SOURCE_DIR}/lib/libglfw3.a" OR EXISTS "${CMAKE_SOURCE_DIR}/lib/glfw3.lib")
    set(USE_LOCAL_GLFW ON)
endif()

if(USE_LOCAL_GLFW)
    message(STATUS "Using local static GLFW from /lib")
    include_directories(${CMAKE_SOURCE_DIR}/include)  # for GLFW/glfw3.h
    link_directories(${CMAKE_SOURCE_DIR}/lib)
else()
    message(STATUS "Fetching GLFW from GitHub")
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw.git
      GIT_TAG 3.3.8
    )
    FetchContent_MakeAvailable(glfw)
endif()

# === GLAD ===
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# === Sources ===
set(SOURCES
    src/main.cpp
    src/Surface.cpp
    src/Cell.cpp
    src/Grid.cpp
    algorithms/Rothermel.cpp
)

# === Executable ===
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/config
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/algorithms
    ${CMAKE_SOURCE_DIR}/src/config
)

# === Pass shader paths as compile definitions ===
target_compile_definitions(${PROJECT_NAME} PRIVATE
    VERTEX_SHADER_PATH=\"${CMAKE_SOURCE_DIR}/shaders/vertex_shader.glsl\"
    FRAGMENT_SHADER_PATH=\"${CMAKE_SOURCE_DIR}/shaders/fragment_shader.glsl\"
)

# === Debugger dir ===
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# === Linking ===
if(USE_LOCAL_GLFW)
    if(MSVC)
        target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 glad opengl32 gdi32)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE libglfw3.a glad ${OPENGL_LIBRARIES})
    endif()
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad OpenGL::GL ${CMAKE_DL_LIBS})
endif()

# === Copy shaders to build dir (optional) ===
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
