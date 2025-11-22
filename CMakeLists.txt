cmake_minimum_required(VERSION 3.16)
project(AuthScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# SQLite3
find_package(SQLite3 REQUIRED)

# Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Source library (for testing)
add_library(AuthScreenLib
    src/Database.cpp
    src/AuthScreen.cpp
    src/PasswordValidator.cpp
)

target_include_directories(AuthScreenLib PUBLIC include)

target_link_libraries(AuthScreenLib
    sfml-graphics
    sfml-window
    sfml-system
    SQLite::SQLite3
)

# Main executable
add_executable(AuthScreen
    src/main.cpp
)

target_link_libraries(AuthScreen
    AuthScreenLib
)

# Tests
add_subdirectory(tests)
