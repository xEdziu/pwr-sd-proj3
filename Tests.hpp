#pragma once
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>

#include "./OpenAddressing.hpp"
#include "./ClosedAddressingWithBST.hpp"
#include "./CuckooHashing.hpp"

namespace fs = std::filesystem;

class Tests
{
 private:

    std::vector<std::string> gatherData() {
        for (const auto& entry : fs::directory_iterator("./data")) {
            files.push_back(entry.path().string());
        }
        return files;
    };
    
 public:
    std::vector<std::string> files;

    Tests() {
        gatherData();
    }

    ~Tests() {
        files.clear();
    }
};

