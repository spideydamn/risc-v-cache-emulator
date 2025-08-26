#include <iostream>
#include <string>
#include <cstring>

#include "emulator.h"

enum class Replacement {
    BOTH,
    LRU,
    bit_pLRU
};


void CheckReplacement(Replacement& destination, char*& arg) {
    if (std::strlen(arg) != 1) {
        std::cerr << "Invalid replacement argument"<< std::endl;
        exit(1);
    }
    switch (arg[0]) {
        case '0':
            destination = Replacement::BOTH;
            break;
        case '1':
            destination = Replacement::LRU;
            break;
        case '2':
            destination = Replacement::bit_pLRU;
            break;
        default:
            std::cerr << "Invalid replacement argument"<< std::endl;
            exit(1);
    }
}

void Parse(const int argc, char**& argv, Replacement& replacement, std::string& assembler, std::string& bin) {
    if (argc != 3 && argc != 5 && argc != 7) {
        std::cerr << "Wrong number of arguments" << std::endl;
        exit(1);
    }

    for (int i = 1; i < argc; i += 2) {
        if (!std::strcmp(argv[i], "--replacement")) {
            CheckReplacement(replacement, argv[i + 1]);
        } else if (!std::strcmp(argv[i], "--asm")) {
            assembler = std::string(argv[i + 1]);
        } else if (!std::strcmp(argv[i], "--bin")) {
            bin = std::string(argv[i + 1]);
        } else {
            std::cerr << "Invalid argument"<< std::endl;
            exit(1);
        }
    }
}

void Emulate(ExclusionPolicy exclusion_policy, const std::string& assembler, const std::string& bin) {
    Emulator emulator(exclusion_policy);

    emulator.Serialize(assembler, bin);
    emulator.Deserialize(bin);

    emulator.ShowStats();
}

int _CRT_glob = 0;

int main(int argc, char** argv) {
    Replacement replacement = Replacement::BOTH;
    std::string assembler = "rv32.asm";
    std::string bin = "serial.bin";

    Parse(argc, argv, replacement, assembler, bin);

    Emulator emulator;
    switch (replacement) {
        case Replacement::BOTH:
            Emulate(ExclusionPolicy::LRU, assembler, bin);
            Emulate(ExclusionPolicy::bit_pLRU, assembler, bin);
            break;
        case Replacement::LRU:
            Emulate(ExclusionPolicy::LRU, assembler, bin);
            break;
        case Replacement::bit_pLRU:
            Emulate(ExclusionPolicy::bit_pLRU, assembler, bin);
            break;
    }

    return 0;
}