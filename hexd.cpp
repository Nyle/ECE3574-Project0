#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide a file to print\n";
        return EXIT_FAILURE;
    } else if (argc > 2) {
        std::cerr << "Please only provide one argument\n";
        return EXIT_FAILURE;
    }
    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "There was an error opening the specified file\n";
        std::cerr << "verify that it exists\n";
    }

    std::cout << "Things would be happening here!\n";
    
    return EXIT_SUCCESS;
}
