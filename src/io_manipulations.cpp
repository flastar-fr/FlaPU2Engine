#include "io_manipulations.hpp"

#include <fstream>
#include <iostream>
#include <ostream>

std::vector<std::string> read_file(const std::string& file_name) {
    std::vector<std::string> file_lines;
    if (std::ifstream file("ressources/" + file_name); file.is_open()) {
        std::string line;

        while (getline(file, line)) {
            file_lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Cannot open file!" << std::endl;
    }

    return file_lines;
}
