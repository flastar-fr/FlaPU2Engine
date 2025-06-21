#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include <map>
#include <string>
#include <vector>


class Preprocessor {
public:
    explicit Preprocessor(const std::vector<std::string>& lines): lines(lines), labels({}) {}

    std::vector<std::string>& preprocess();
    void uniformize();
    void findLabels();
    void replaceLabels();

private:
    std::vector<std::string> lines;
    std::map<std::string, std::string> labels;
};


#endif //PREPROCESSOR_HPP
