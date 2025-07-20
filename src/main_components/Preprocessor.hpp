#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include <string>
#include <unordered_map>
#include <vector>


class Preprocessor {
public:
    explicit Preprocessor(const std::vector<std::string>& lines): lines(lines), labels_n_definitions({}) {}

    std::vector<std::string>& preprocess();
    void uniformize();
    void findDefinition();
    void findLabels();
    void mergePortsLabelsToLabels();
    void replaceLabelsNDefinitions();
    void processPatternRepetitions();

private:
    std::vector<std::string> lines;
    std::unordered_map<std::string, std::string> labels_n_definitions;
};


#endif //PREPROCESSOR_HPP
