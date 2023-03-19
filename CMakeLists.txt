cmake_minimum_required(VERSION 3.24)
project(compress_dcompress)

set(CMAKE_CXX_STANDARD 14)

# Find the Boost libraries (specifically version 1.72 or higher), including filesystem and system libraries (required for Boost I/O Streams)
find_package(Boost 1.72 REQUIRED COMPONENTS filesystem system)

# Find the zlib library (specifically version 1.2.11 or higher), required for Boost I/O Streams to work, and link against it
find_package(ZLIB 1.2.11 REQUIRED)

# Add your source files here,
set(SOURCES
        compress_dcompress.cpp
        )

# Add your executable target, and link against the Boost libraries and zlib
add_executable(compress_dcompress ${SOURCES})

# Link against the Boost libraries and zlib, and set the include directories for the Boost libraries
target_link_libraries(compress_dcompress PRIVATE Boost::filesystem Boost::system ${ZLIB_LIBRARIES})
target_include_directories(compress_dcompress PRIVATE ${Boost_INCLUDE_DIRS})

# Set the installation path to CMAKE_INSTALL_BINDIR by default (this is the appropriate directory for binary installation on the current platform)
include(GNUInstallDirs)
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_BINDIR}")
endif ()

# Install the compress_dcompress binary
install(TARGETS compress_dcompress
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        )
