#pragma once

#include "parser.h"

class Preprocessor {
public:
    static void calculate(const std::vector<CommandToken>& program, CPUMemory& memory) {
        CommandToken instruction;
        while (memory.GetProgramCounter() < program.size() * kInstructionSize) {
            instruction = program[memory.GetProgramCounter() / 4];
            token_to_class[instruction.command]->execute(instruction.operands, memory);
        }
    }
};