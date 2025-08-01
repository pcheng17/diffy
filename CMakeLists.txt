cmake_minimum_required(VERSION 3.20)

project(diffy
    VERSION 1.0.0
    DESCRIPTION "Modern C++ Automatic Differentiation Library"
    LANGUAGES CXX
)


# Set C++23 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Debug/Release configurations
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Create the main library as header-only
add_library(diffy INTERFACE)

# Set include directories
target_include_directories(diffy INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Require C++23 features
target_compile_features(diffy INTERFACE cxx_std_23)

# Optional: Find and link additional libraries if needed
# find_package(Eigen3 REQUIRED)
# target_link_libraries(autodiff INTERFACE Eigen3::Eigen)

# Examples executable
# add_executable(examples
#     examples/basic_usage.cpp
#     examples/forward_mode.cpp
# )
#
# target_link_libraries(examples PRIVATE autodiff)

# Testing with doctest
enable_testing()

# Find or fetch doctest
find_package(doctest QUIET)
if(NOT doctest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG        v2.4.12
    )
    FetchContent_MakeAvailable(doctest)
endif()

# Test executable
add_executable(tests
    tests/main.cpp
    tests/DualTests.cpp
    tests/DualMathTests.cpp
)

target_link_libraries(tests
    PRIVATE
    diffy
    doctest::doctest
)

# Add tests to CTest
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(tests)

# Installation (optional)
# include(GNUInstallDirs)

# install(TARGETS autodiff
#     EXPORT AutoDiffTargets
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
#
# install(DIRECTORY include/
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
#
# install(EXPORT AutoDiffTargets
#     FILE AutoDiffTargets.cmake
#     NAMESPACE AutoDiff::
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AutoDiff
# )
