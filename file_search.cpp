#include "file_search.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <vector>

namespace fs = std::filesystem;

namespace {
    std::atomic<bool> fileFound(false);
    std::mutex foundMutex;
}

void searchInDirectory(const std::string& root, const std::string& target) {
    for (const auto& entry : fs::directory_iterator(root)) {
        if (fileFound)
            return;

        if (entry.is_directory()) {
            std::vector<std::thread> threads;
            threads.reserve(8);

            for (const auto& subEntry : fs::directory_iterator(entry.path())) {
                if (fileFound)
                    break;

                if (subEntry.is_directory()) {
                    threads.emplace_back(searchInDirectory, subEntry.path().string(), target);
                }
                else if (subEntry.is_regular_file() && subEntry.path().filename() == target) {
                    std::lock_guard<std::mutex> lock(foundMutex);
                    if (!fileFound) {
                        std::cout << "File found: " << subEntry.path().string() << std::endl;
                        fileFound = true;
                    }
                }
            }

            for (auto& thread : threads) {
                if (thread.joinable())
                    thread.join();
            }
        }
        else if (entry.is_regular_file() && entry.path().filename() == target) {
            std::lock_guard<std::mutex> lock(foundMutex);
            if (!fileFound) {
                std::cout << "File found: " << entry.path().string() << std::endl;
                fileFound = true;
            }
        }
    }
}

bool FileSearch::searchFile(const std::string& rootDirectory, const std::string& fileName) {
    fileFound = false;
    searchInDirectory(rootDirectory, fileName);
    return fileFound;
}

