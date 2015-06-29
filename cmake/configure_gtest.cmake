# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/thirdparty/googletest)
set(GTEST_BINARY_DIR ${GTEST_ROOT}/bin)

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    URL_MD5 2d6ec8ccdf5c46b05ba54a9fd1d130d7
    PREFIX ${GTEST_ROOT}
    # Disable install step
    INSTALL_COMMAND ""
    BINARY_DIR ${GTEST_BINARY_DIR}
    SOURCE_DIR ${GTEST_ROOT}/src/googletest
    CMAKE_ARGS
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    BUILD_BYPRODUCTS ${GTEST_BINARY_DIR}/libgtest.a ${GTEST_BINARY_DIR}/libgtest_main.a
)

# Create a gtest target to be used as a dependency by test programs
add_library(gtest IMPORTED STATIC GLOBAL)
add_dependencies(gtest googletest)

add_library(gtest_main IMPORTED STATIC GLOBAL)
add_dependencies(gtest_main googletest)

# Set googletest properties
set_target_properties(gtest PROPERTIES
    "IMPORTED_LOCATION" "${GTEST_BINARY_DIR}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
set_target_properties(gtest_main PROPERTIES
    "IMPORTED_LOCATION" "${GTEST_BINARY_DIR}/libgtest_main.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories(${GTEST_ROOT}/src/googletest/include)