# Time Traveler's Compressor

## compress_decompress

A console application designed to help a time traveler, who got stuck in the past in the dinosaur era, send logs from a malfunctioning time machine to engineers in the present. The application must efficiently compress and decompress logs to minimize resource usage and data size. This console application is built using C++, zlib, and Boost Filesystem library.

## Problem Context

The time traveler is stuck in the past, and the time machine is running out of power. The engineers need logs from the time machine to fix the issue, but the time traveler can only send a single file using the time machine's limited capabilities. The logs are in both textual and binary formats and are scattered across multiple folders. Some log files are binary identical but located in different folders with different names.

The objective is to create an efficient console application in C++ that can:

- Traverse the file structure (with subfolders) starting from a specified folder.
- Compress the folder's content into a single file in an efficient way in terms of both resource usage and produced file size.
- "Unpack" the compressed file, restoring the original folder and file structure and content.

## Assumptions

- Each file size does not exceed 2GB.
- The number of files does not exceed 1,048,576.
- The time machine's disk capacity is sufficient to at least make a copy of the whole logs folder.

## Solution

The provided Simple File Compressor solution can be used to address this problem. It's a console application that uses zlib for compression and Boost Filesystem library for file manipulation. It meets the requirements and constraints described in the problem context.

## How to Use

Please follow the instructions in the README for building and using the Simple File Compressor. The time traveler can use this application to compress the logs into a single file and then send the compressed file to the engineers. The engineers can then use the same application to decompress the file and access the logs to fix the time machine issue.

Remember, the time traveler is in a dangerous situation and starving, so hurry up and send the Simple File Compressor to help them out!

## Dependencies

- Boost Filesystem Library: [https://www.boost.org/doc/libs/1_77_0/libs/filesystem/doc/index.htm](https://www.boost.org/doc/libs/1_77_0/libs/filesystem/doc/index.htm)
- zlib Compression Library: [https://zlib.net/](https://zlib.net/)

## How to build with CMake

1. Install the dependencies (Boost and zlib).

   Install Boost:
   ```bash
    # sudo apt-get install libboost-all-dev # Boost linux installation
   
   brew install boost # Boost macOS installation
    ```
   Install zlib:
   ```bash
    # sudo apt-get install zlib1g-dev # zlib linux installation
   
    brew install zlib # macOS installation
    ```
   
   Added boost and zlid paths to ~/.bash_profile or ~/.zshrc:

   ```bash # Boost brew installation
    echo 'export BOOST_ROOT=/opt/homebrew/Cellar/boost/1.81.0_1' >> ~/.zshrc
    echo 'export BOOST_LIBRARYDIR=/opt/homebrew/Cellar/boost/1.81.0_1/lib' >> ~/.zshrc
    echo 'export BOOST_INCLUDEDIR=/opt/homebrew/Cellar/boost/1.81.0_1/include' >> ~/.zshrc
    ```  
    ```bash # zlib brew installation
   echo 'export ZLIB_ROOT=/opt/homebrew/Cellar/zlib/1.2.13' >> ~/.zshrc
   echo 'export ZLIB_LIBRARYDIR=/opt/homebrew/Cellar/zlib/1.2.13/lib' >> ~/.zshrc
   echo 'export ZLIB_INCLUDEDIR=/opt/homebrew/Cellar/zlib/1.2.13/include' >> ~/.zshrc
   ```
   
    Reload the profile:
    ```bash
    source ~/.zshrc
    ```
    
2. Create a `CMakeLists.txt` file in the project directory with the following content:

```cmake
cmake_minimum_required(VERSION 3.24)
project(compress_dcompress)

set(CMAKE_CXX_STANDARD 14)

# Find the Boost libraries (specifically version 1.72 or higher), including filesystem and system libraries (required for Boost I/O Streams)
find_package(Boost 1.72 REQUIRED COMPONENTS filesystem system)

# Find the zlib library (specifically version 1.2.11 or higher), required for Boost I/O Streams to work, and link against it
find_package(ZLIB 1.2.11 REQUIRED)

# Add your source files here,
set(SOURCES compress_dcompress.cpp)

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
install(TARGETS compress_dcompress RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

```
3. Create a build directory and navigate to it:

   ```bash
   mkdir build && cd build
    ```

4. Run CMake to generate the build files:
   ```bash
   cmake ..
   ```
   
5. Build the project:

   ```bash
   make 
   ```
The compiled binary `compress_decompress` will be created in the `build` directory.

## Usage
#### Compress a directory 
   ```bash
   ./compress_decompress compress /path/to/input/directory /path/to/output/compressed_file
   ```
#### Decompress a directory 
    ```bash
    ./compress_decompress decompress /path/to/input/compressed_file /path/to/output/directory
    ```
## Example
#### Compress a directory 
   ```bash
   ./compress_decompress compress test_directory compressed_directory.zip
   ```
#### Decompress a directory 
    ```bash
    ./compress_decompress decompress compressed_directory.zip decompressed_directory
    ```


