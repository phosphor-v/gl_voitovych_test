#include <iostream>
#include "file_search.h"

int main() {
    std::string fileName;
    std::cout << "Enter the name of the file to search: ";
    std::cin >> fileName;

    std::string rootDirectory = "C:\\";

    if (FileSearch::searchFile(rootDirectory, fileName)) {
        std::cout << "File found." << std::endl;
    }
    else {
        std::cout << "File not found." << std::endl;
    }

    return 0;
}
