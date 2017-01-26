#include <iostream>
#include <fstream>
#include <cstdlib>

const int CHARS_PER_LINE = 16;

void printline(uint8_t line[], unsigned int charcounter);

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
    // How many characters we have read
    unsigned int charcounter = 0; 
    uint8_t line[CHARS_PER_LINE]; // Store the characters in the line
    uint8_t value; // Store the most recently read character
    // Read a character
    file.read(reinterpret_cast<std::fstream::char_type*>(&value), sizeof value);
    while (!file.fail()) {
        line[charcounter++ % CHARS_PER_LINE] = value;
        if (charcounter % CHARS_PER_LINE == 0) {
            printline(line, charcounter);
        }
        // Read the next character
        file.read(reinterpret_cast<std::fstream::char_type*>(&value),
                  sizeof value);
    }
    // Print an incomplete line if there is one
    if (CHARS_PER_LINE != 0) {
        printline(line, charcounter);
    }

    return EXIT_SUCCESS;
}

void printline(uint8_t line[], unsigned int charcounter) {
    int endpos = (charcounter % CHARS_PER_LINE == 0) ? CHARS_PER_LINE :
        (charcounter % CHARS_PER_LINE);
    // Print the start of line character index
    printf("%08x: ", charcounter - endpos);
    // Print the bytes in hex
    for (int i = 0; i < CHARS_PER_LINE; i++) {
        if (i < endpos) {
            // Print the next byte, with a space after every other
            printf(i % 2 ? "%02x " : "%02x", line[i]);
        } else {
            // Fill with spaces if line is incomplete
            printf(i % 2 ? "   " : "  ");
        }
    }
    // End the line
    std::cout << '\n';
    return;
}
