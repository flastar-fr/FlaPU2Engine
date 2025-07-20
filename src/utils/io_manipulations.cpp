#include "io_manipulations.hpp"

#include <fstream>
#include <iostream>
#include <ostream>

bool read_file(const std::string& file_path, std::vector<std::string>& result) {
    if (std::ifstream file(file_path); file.is_open()) {
        std::string line;

        while (getline(file, line)) {
            result.push_back(line);
        }
        file.close();
    }
    else {
        std::cerr << "Cannot open file!" << std::endl;
        return false;
    }

    return true;
}
