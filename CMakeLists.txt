cmake_minimum_required(VERSION 3.10)
project(ForestFireSim)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Include glad and other headers
include_directories(include)

# Add source files
add_executable(ForestFireSim
    src/main.cpp
)

# Link libraries depending on platform
#if (WIN32)
    # Assuming GLFW is installed system-wide or via vcpkg
    # find_package(glfw3 CONFIG REQUIRED)
    # target_link_libraries(ForestFireSim)
    
#else()
 #   find_package(OpenGL REQUIRED)
 #   find_package(glfw3 REQUIRED)
 #   target_link_libraries(ForestFireSim PRIVATE glfw OpenGL::GL)
#endif()
