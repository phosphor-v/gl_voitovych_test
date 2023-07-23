#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <string>

class FileSearch {
public:
    static bool searchFile(const std::string& rootDirectory, const std::string& fileName);
};

#endif

