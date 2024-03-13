# Set minimum required CMake version and project information
cmake_minimum_required(VERSION 3.12)
project(OpenGLProject # also the name of the executable
    VERSION 0.0.1
    DESCRIPTION "A DESCRIPTION"
    HOMEPAGE_URL "https://github.com/MrCatNerd/SmallPrograms"
    LANGUAGES CXX
)

# Define source files
file(GLOB_RECURSE _SOURCE_FILES CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Exclude files starting with underscore '_<file>'
list(FILTER _SOURCE_FILES EXCLUDE REGEX ".*\\/_.*\\..*")

# Create executable target
add_executable(${PROJECT_NAME} ${_SOURCE_FILES})

# Set private include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/include"
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD          17
  CXX_STANDARD_REQUIRED ON
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}$<0:>" # Handle resource dependencies
)

# Add general OpengGL package
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLProject PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(OpenGLProject PRIVATE ${OPENGL_INCLUDE_DIR})

# Add GLEW package
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

# Add GLFW package
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile_commands.json (you don't need this i got a thingy in the Makefile that does the same thing)

