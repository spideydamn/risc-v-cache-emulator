#pragma once

#include "exclusion_policy.h"
#include "deserializer.h"
#include "preprocessor.h"

class Emulator {
private:
    CPUMemory memory;
    ExclusionPolicy exclusion_policy;
public:
    Emulator(ExclusionPolicy exclusion_policy = ExclusionPolicy::LRU) : 
        exclusion_policy(exclusion_policy),
        memory(CPUMemory(exclusion_policy)) {}

    void Serialize(const std::string& read_path, const std::string& write_path) const {
        Parser::ReadFile(read_path, write_path);
    }

    void Deserialize(const std::string& serial_file) {
        Deserializer deserializer = Deserializer(serial_file);
        std::vector<CommandToken> commands;
        CommandToken token;
        while (true) {
            token = deserializer.execute();
            if (token.command == OperationCode::NONE) {
                break;
            }
            commands.push_back(token);
        }
        Preprocessor::calculate(commands, memory);
    }

    void ShowStats() const {
        switch (exclusion_policy) {
            case ExclusionPolicy::LRU:
                printf("LRU\thit rate: %3.4f%%\n", (100 * (double)memory.GetHits() / (double)(memory.GetHits() + memory.GetMisses())));
                break;
            case ExclusionPolicy::bit_pLRU:
                printf("pLRU\thit rate: %3.4f%%\n", (100 * (double)memory.GetHits() / (double)(memory.GetHits() + memory.GetMisses())));
                break;
        }
    }
};
