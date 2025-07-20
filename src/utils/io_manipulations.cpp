#include "io_manipulations.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <tinyfiledialogs.h>

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

std::string open_file_dialog() {
    const char* filters[] = {"*.asm"};

    const auto path = tinyfd_openFileDialog(
        "Select an asm file to execute",
        "",
        1,
        filters,
        ".asm",
        0
    );

    if (!path) {
        return "";
    }

    return {path};
}

json open_json_file(const std::string& config_file_name) {
    auto file = std::ifstream(config_file_name);
    if (!file) {
        std::cerr << "Cannot open file" << std::endl;
        throw std::runtime_error("Cannot open file");
    }

    json json_file;
    file >> json_file;
    return json_file;
}
