cmake_minimum_required(VERSION 3.24)
project(compress_dcompress)

set(CMAKE_CXX_STANDARD 14)

# Find the Boost libraries, including filesystem and system libraries (required for Boost I/O Streams) and zlib
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Find the zlib library, required for Boost I/O Streams to work, and link against it
find_package(ZLIB REQUIRED)

# Add your source files here,
set(SOURCES
        compress_dcompress.cpp
        )

# Add your executable target, and link against the Boost libraries and zlib
add_executable(compress_dcompress ${SOURCES})

# Link against the Boost libraries and zlib, and set the include directories for the Boost libraries
target_link_libraries(compress_dcompress PRIVATE Boost::filesystem Boost::system ${ZLIB_LIBRARIES})

# Set the installation path, if not already set, to /usr/local by default (this is the default for most Linux distributions)
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif ()

# Install the compress_dcompress binary, and set the installation path to /usr/local/bin by default (this is the default for most Linux distributions)
install(TARGETS compress_dcompress
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        )
