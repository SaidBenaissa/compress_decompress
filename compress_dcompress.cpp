#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>

// Compress the data and store it in the output file
void compress_and_store(const boost::filesystem::path &input_path, const
std::string &output_file) {
    std::ofstream output;
    output.open(output_file, std::ios::binary);
    std::vector<char> buffer;

    // Iterate over all files in the input path recursively and compress them one by one into the output file
    for (boost::filesystem::recursive_directory_iterator it(input_path), end; it != end; ++it) {

        // Check if the current path is a file and not a directory or a symlink to a directory
        if (!boost::filesystem::is_directory(it->status())) {

            // Read the file into a buffer
            std::ifstream input;

            // Open the file in binary mode to avoid any text transformations
            input.open(it->path().string(), std::ios::binary);

            // Read the file into the buffer
            buffer.assign(std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>());

            // Compress the buffer
            uLong compressed_size = compressBound(buffer.size());

            // Allocate a buffer for the compressed data, compress the data and write it to the output file
            std::vector<char> compressed_buffer(compressed_size);

            // Compress the data, the destination buffer must be large enough to hold the compressed data
            compress(reinterpret_cast<Bytef *>(compressed_buffer.data()),&compressed_size, reinterpret_cast<const Bytef *>(buffer.data()),buffer.size());

            // Write the file path to the output file, followed by the compressed size and the compressed data
            output.write(it->path().string().c_str(), it->path().string().size() + 1);

            // Write the compressed size to the output file, followed by the compressed data, the size is needed to decompress the data later
            output.write(reinterpret_cast<const char *>(&compressed_size),sizeof(compressed_size));

            // Write the compressed data to the output file, the size is needed to decompress the data later, the size is needed to decompress the data later
            output.write(compressed_buffer.data(), compressed_size);
        }
    }
}

// Decompress the data and restore the files

void decompress_and_restore(const std::string &input_file, const boost::filesystem::path &output_path) {
    // Open the input file for reading
    std::ifstream input;
    input.open(input_file, std::ios::binary);

    // Read the input file until the end of the file
    while (!input.eof()) {
        // Read the file path
        std::string file_path;
        std::getline(input, file_path, '\0');

        // Check if the file path is not empty
        if (!file_path.empty()) {
            // Read the compressed size of the file
            uLong compressed_size;
            input.read(reinterpret_cast<char *>(&compressed_size),
                       sizeof(compressed_size));

            // Read the compressed data into a buffer
            std::vector<char> compressed_buffer(compressed_size);
            input.read(compressed_buffer.data(), compressed_size);

            // Decompress the buffer
            unsigned long long uncompressed_size =
                    2ULL * 1024 * 1024 * 1024; // Max file size: 2GB
            std::vector<char> buffer(uncompressed_size);
            uLong destination_size = static_cast<uLong>(uncompressed_size);
            uncompress(reinterpret_cast<Bytef *>(buffer.data()), &destination_size,
                       reinterpret_cast<const Bytef *>(compressed_buffer.data()),
                       compressed_size);

            // Create parent directories for the file path
            boost::filesystem::create_directories(
                    (output_path / file_path).parent_path());

            // Open the output file for writing
            std::ofstream output;
            output.open((output_path / file_path).string(), std::ios::binary);

            // Write the decompressed data to the output file
            output.write(buffer.data(), destination_size);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct, if not print the usage and exit
    if (argc < 4) {
        std::cout << "Usage: " << argv[0]
                  << " [compress|decompress] <input_directory_path> <output_directory_path>"
                  << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    boost::filesystem::path input_path(argv[2]);
    boost::filesystem::path output_path(argv[3]);

    if (mode == "compress") {
        // Compression in progress
        std::cout << input_path << " compressiong ..." << std::endl;
        compress_and_store(input_path, output_path.string());
    } else if (mode == "decompressiong ...") {
        decompress_and_restore(input_path.string(), output_path);
    } else {
        std::cout << "Invalid mode. Please use 'compress' or 'decompress' as the "
                     "first argument."
                  << std::endl;
        return 1;
    }

    return 0;
}
