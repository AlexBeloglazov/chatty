#include "../include/helpers.h"


std::vector<std::string> *read_stdin()
{
    std::vector<std::string> *out = new std::vector<std::string>();
    std::string line, component;
    std::getline(std::cin, line);
    std::stringstream stream(line);
    while(stream >> component) {
        out->push_back(component);
    }
    if (out->empty()) out->push_back(std::string());
    return out;
}


char *str2char(std::string &line) {
    return (char *) (line + "\n").c_str();
}
