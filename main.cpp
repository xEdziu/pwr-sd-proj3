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

OpenAddressing<int, std::string> *openAddressing;
ClosedAddressingWithBST<int, std::string> *closedAddressing;
CuckooHashing<int, std::string> *cuckooHashing;

template <typename Structure>
uint64_t performInsertion(Structure *structure, int key, std::string value) {
    auto start = std::chrono::high_resolution_clock::now();
    structure->insert(key, value);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename Structure>
uint64_t performRemoval(Structure *structure, int key) {
    auto start = std::chrono::high_resolution_clock::now();
    structure->remove(key);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename Structure>
int populateStructureAndReturnKeyToRemove(Structure *structure, std::string file) {
    std::ifstream input(file);
    std::string line;
    std::cout << "Populating structure with data from " << file << "\n";
    while (std::getline(input, line)) {
        int key = std::stoi(line.substr(0, line.find(" ")));
        std::string value = line.substr(line.find(" ") + 1);
        structure->insert(key, value);
    }
    std::cout << "Structure populated\n";
    bool found = false;
    int tempKey = -5;
    while (!found) {
        tempKey = rand()%1000000 + 1;
        found = structure->exists(tempKey);
    }
    return tempKey;
}

int main() {
    std::cout << "Starting structure testing...\n";
    std::ofstream output("results.csv");
    output << "action;structure;size;timeNs\n";
    int line = 0;

    int dataSets[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000};

    auto mainStart = std::chrono::high_resolution_clock::now();

    // Open Addressing, Insertion and Deletion
    for (int probingType = 0; probingType < 3; probingType++) {
        std::cout << "Open Addressing, probing type: " << probingType << "\n";
        for (int size : sizes){
            uint64_t timeInsert = 0;
            uint64_t timeRemove = 0;
            for (int set : dataSets) {
                std::string filename = "./data/zbior_" + std::to_string(set) + "_rozmiar_" + std::to_string(size) + ".txt";
                int keyToRemove;
                std::cout << "Open Addressing, probing type: " << probingType << ", size: " << size << ", set: " << set << "\n";
                for (int j = 1; j <= 100; j++){
                    openAddressing = new OpenAddressing<int, std::string>(probingType, size);
                    keyToRemove = populateStructureAndReturnKeyToRemove(openAddressing, filename);
                    std::cout << "OPEN_ADDRESSING | Performing insertion for size: " << size << ", set: " << set << "\n";
                    timeInsert += performInsertion(openAddressing, j, "test");
                    delete openAddressing;
                    openAddressing = new OpenAddressing<int, std::string>(probingType, size);
                    keyToRemove = populateStructureAndReturnKeyToRemove(openAddressing, filename);
                    std::cout << "OPEN_ADDRESSING | Performing removal for size: " << size << ", set: " << set << "\n";
                    timeRemove += performRemoval(openAddressing, keyToRemove);
                    delete openAddressing;
                }
            }
            output << "insert;openAddressingProbingType"<< probingType << ";" << size << ";" << timeInsert / 1000 << "\n";
            output << "remove;openAddressingProbingType"<< probingType << ";" << size << ";" << timeRemove / 1000 << "\n";
        }
    }

    // Closed Addressing, Insertion and Deletion
    for (int size : sizes){
        uint64_t timeInsert = 0;
        uint64_t timeRemove = 0;
        for (int set : dataSets) {
            std::string filename = "./data/zbior_" + std::to_string(set) + "_rozmiar_" + std::to_string(size) + ".txt";
            int keyToRemove;
            std::cout << "Closed Addressing, size: " << size << ", set: " << set << "\n";
            for (int j = 1; j <= 100; j++){
                closedAddressing = new ClosedAddressingWithBST<int, std::string>(size);
                keyToRemove = populateStructureAndReturnKeyToRemove(closedAddressing, filename);
                std::cout << "CLOSED_ADDRESSING | Performing insertion for size: " << size << ", set: " << set << "\n";
                timeInsert += performInsertion(closedAddressing, j, "test");
                delete closedAddressing;
                closedAddressing = new ClosedAddressingWithBST<int, std::string>(size);
                keyToRemove = populateStructureAndReturnKeyToRemove(closedAddressing, filename);
                std::cout << "CLOSED_ADDRESSING | Performing removal for size: " << size << ", set: " << set << "\n";
                timeRemove += performRemoval(closedAddressing, keyToRemove);
                delete closedAddressing;
            }
        }
        output << "insert;closedAddressing;" << size << ";" << timeInsert / 1000 << "\n";
        output << "remove;closedAddressing;" << size << ";" << timeRemove / 1000 << "\n";
    }

    // Cuckoo Hashing, Insertion and Deletion
    for (int size : sizes){
        uint64_t timeInsert = 0;
        uint64_t timeRemove = 0;
        for (int set : dataSets) {
            std::string filename = "./data/zbior_" + std::to_string(set) + "_rozmiar_" + std::to_string(size) + ".txt";
            int keyToRemove;
            std::cout << "Cuckoo Hashing, size: " << size << ", set: " << set << "\n";
            for (int j = 1; j <= 100; j++){
                cuckooHashing = new CuckooHashing<int, std::string>(size);
                keyToRemove = populateStructureAndReturnKeyToRemove(cuckooHashing, filename);
                std::cout << "CUCKOO_HASHING | Performing insertion for size: " << size << ", set: " << set << "\n";
                timeInsert += performInsertion(cuckooHashing, j, "test");
                delete cuckooHashing;
                cuckooHashing = new CuckooHashing<int, std::string>(size);
                keyToRemove = populateStructureAndReturnKeyToRemove(cuckooHashing, filename);
                std::cout << "CUCKOO_HASHING | Performing removal for size: " << size << ", set: " << set << "\n";
                timeRemove += performRemoval(cuckooHashing, keyToRemove);
                delete cuckooHashing;
            }
        }
        output << "insert;cuckooHashing;" << size << ";" << timeInsert / 1000 << "\n";
        output << "remove;cuckooHashing;" << size << ";" << timeRemove / 1000 << "\n";
    }

    auto mainEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Structure testing finished\n";
    std::cout << "Total time: " << std::chrono::duration_cast<std::chrono::minutes>(mainEnd - mainStart).count() << "s\n";

    return 0;
}