#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "command_token.h"
#include "memory.h"

const uint8_t kInstructionSize = 4;

inline std::unordered_map<std::string, uint32_t> bin_register = {
        {"zero", 0},
        {"ra",   1},
        {"sp",   2},
        {"gp",   3},
        {"tp",   4},
        {"t0",   5},
        {"t1",   6},
        {"t2",   7},
        {"s0",   8},
        {"fp",   8},
        {"s1",   9},
        {"a0",   10},
        {"a1",   11},
        {"a2",   12},
        {"a3",   13},
        {"a4",   14},
        {"a5",   15},
        {"a6",   16},
        {"a7",   17},
        {"s2",   18},
        {"s3",   19},
        {"s4",   20},
        {"s5",   21},
        {"s6",   22},
        {"s7",   23},
        {"s8",   24},
        {"s9",   25},
        {"s10",  26},
        {"s11",  27},
        {"t3",   28},
        {"t4",   29},
        {"t5",   30},
        {"t6",   31},
        {"ZERO", 0},
        {"RA",   1},
        {"SP",   2},
        {"GP",   3},
        {"TP",   4},
        {"T0",   5},
        {"T1",   6},
        {"T2",   7},
        {"S0",   8},
        {"FP",   8},
        {"S1",   9},
        {"A0",   10},
        {"A1",   11},
        {"A2",   12},
        {"A3",   13},
        {"A4",   14},
        {"A5",   15},
        {"A6",   16},
        {"A7",   17},
        {"S2",   18},
        {"S3",   19},
        {"S4",   20},
        {"S5",   21},
        {"S6",   22},
        {"S7",   23},
        {"S8",   24},
        {"S9",   25},
        {"S10",  26},
        {"S11",  27},
        {"T3",   28},
        {"T4",   29},
        {"T5",   30},
        {"T6",   31},
        {"x0",   0},
        {"x1",   1},
        {"x2",   2},
        {"x3",   3},
        {"x4",   4},
        {"x5",   5},
        {"x6",   6},
        {"x7",   7},
        {"x8",   8},
        {"x9",   9},
        {"x10",  10},
        {"x11",  11},
        {"x12",  12},
        {"x13",  13},
        {"x14",  14},
        {"x15",  15},
        {"x16",  16},
        {"x17",  17},
        {"x18",  18},
        {"x19",  19},
        {"x20",  20},
        {"x21",  21},
        {"x22",  22},
        {"x23",  23},
        {"x24",  24},
        {"x25",  25},
        {"x26",  26},
        {"x27",  27},
        {"x28",  28},
        {"x29",  29},
        {"x30",  30},
        {"x31",  31},
        {"X0",   0},
        {"X1",   1},
        {"X2",   2},
        {"X3",   3},
        {"X4",   4},
        {"X5",   5},
        {"X6",   6},
        {"X7",   7},
        {"X8",   8},
        {"X9",   9},
        {"X10",  10},
        {"X11",  11},
        {"X12",  12},
        {"X13",  13},
        {"X14",  14},
        {"X15",  15},
        {"X16",  16},
        {"X17",  17},
        {"X18",  18},
        {"X19",  19},
        {"X20",  20},
        {"X21",  21},
        {"X22",  22},
        {"X23",  23},
        {"X24",  24},
        {"X25",  25},
        {"X26",  26},
        {"X27",  27},
        {"X28",  28},
        {"X29",  29},
        {"X30",  30},
        {"X31",  31},
};

inline std::unordered_map<uint32_t, std::string> bin_to_string_register = {
        {0, "zero"},
        {1, "ra"},
        {2, "sp"},
        {3, "gp"},
        {4, "tp"},
        {5, "t0"},
        {6, "t1"},
        {7, "t2"},
        {8, "s0"},
        {9, "s1"},
        {10, "a0"},
        {11, "a1"},
        {12, "a2"},
        {13, "a3"},
        {14, "a4"},
        {15, "a5"},
        {16, "a6"},
        {17, "a7"},
        {18, "s2"},
        {19, "s3"},
        {20, "s4"},
        {21, "s5"},
        {22, "s6"},
        {23, "s7"},
        {24, "s8"},
        {25, "s9"},
        {26, "s10"},
        {27, "s11"},
        {28, "t3"},
        {29, "t4"},
        {30, "t5"},
        {31, "t6"},
};


inline bool is_number(const std::string& s) {
    if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        bool is_number = true;
        for (int i = 2; i < s.size(); ++i) {
            if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'f') && (s[i] < 'A' || s[i] > 'F')) {
                is_number = false;
            }
        }
        return is_number;
    }
    long long count = 0;
    for (char i : s) {
        count += (bool)isdigit(i);
    }
    return (count == s.size()) || (s[0] == '-' && count == s.size() - 1);
}

inline int32_t str_to_num(const std::string& s) {
    int32_t num = 0;
    int32_t place = 1;
    if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        for (int8_t i = s.size() - 1; i >= 2; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                num += place * (s[i] - '0');
                place *= 16;
            }
            if (s[i] >= 'a' && s[i] <= 'f') {
                num += place * (s[i] - 'a');
                place *= 16;
            }
            if (s[i] >= 'A' && s[i] <= 'F') {
                num += place * (s[i] - 'A');
                place *= 16;
            }
        }
        return num;
    }
    if (s[0] == '-') {
        for (int8_t i = s.size() - 1; i >= 1; --i) {
            num += place * (s[i] - '0');
            place *= 10;
        }
        return -num;
    }
    for (int8_t i = s.size() - 1; i >= 0; --i) {
        num += place * (s[i] - '0');
        place *= 10;
    }
    return num;
}


inline void ParseNumber(const std::string& src, int32_t& dest) {
    if (is_number(src)) {
        dest = str_to_num(src);
    } else {
        std::cerr << "preprocessor error: \"" << src << "\" is not a number\n";
        exit(1);
    }
}

inline void ParseNumber(const std::string& src, uint32_t& dest) {
    if (is_number(src)) {
        dest = (uint32_t)str_to_num(src);
    } else {
        std::cerr << "preprocessor error: \"" << src << "\" is not a number\n";
        exit(1);
    }
}

inline void ParseRegister(const std::string& src, int32_t& dest, CPUMemory& memory) {
    if (string_to_register_number.find(src) != string_to_register_number.end()) {
        dest = memory.GetRegister((*string_to_register_number.find(src)).second);
    } else {
        std::cerr << "preprocessor error: \"" << src << "\" is not a register\n";
        exit(1);
    }
}

inline void ParseRegister(const std::string& src, uint32_t& dest, CPUMemory& memory) {
    if (string_to_register_number.find(src) != string_to_register_number.end()) {
        dest = (uint32_t)memory.GetRegister((*string_to_register_number.find(src)).second);
    } else {
        std::cerr << "preprocessor error: \"" << src << "\" is not a register\n";
        exit(1);
    }
}

inline void check_operands_number(const std::vector<std::string>& operands, uint8_t true_size) {
    if (operands.size() != true_size) {
        std::cerr << "preprocessor error: operands.size() = " << operands.size() << ", but true size = " << true_size << '\n';
        exit(1);
    }
}

inline void SetBits(uint32_t& command, const uint8_t left, const uint8_t right, uint32_t line) {
    for (uint8_t i = left; i <= right; ++i) {
        if (line & (uint32_t)1) {
            command |= ((uint32_t)1 << i);
        }
        line >>= 1;
    }
}

inline uint32_t GetBits(const uint32_t command, const uint8_t left, const uint8_t right) {
    uint32_t result = 0;
    for (uint8_t i = right; i >= left; --i) {
        result <<= 1;
        result |= (command >> i) & (uint32_t)1;
    }
    return result;
}

inline std::string BitsToString(uint32_t bits, uint8_t size) {
    return std::to_string((int32_t)((bits & ((1 << (size - 1)) - 1)) - (((bits >> (size - 1)) & (uint32_t)1) << (size - 1))));
}

inline std::string UnorderedBitsToString(uint32_t bits, uint8_t size) {
    return std::to_string(bits);
}





class Operation {
public:
    virtual void execute(const std::vector<std::string>& operands, CPUMemory& memory) = 0;

    virtual uint32_t GetBin(const std::vector<std::string>& operands) = 0;

    virtual void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) = 0;
};

class LUI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 2);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t imm;
        ParseNumber(operands[1], imm);

        rd = imm << 12;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[1], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 13);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::LUI;
        operands.resize(2);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = UnorderedBitsToString(GetBits(bin_command, 12, 31), 20);
    }
};

class AUIPC : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 2);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t& pc = memory.GetProgramCounter();
        int32_t imm;
        ParseNumber(operands[1], imm);

        rd = (int32_t)pc + (imm << 12);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[1], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 5);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::AUIPC;
        operands.resize(2);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = UnorderedBitsToString(GetBits(bin_command, 12, 31), 20);
    }
};

class ADDI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 + imm;

        memory.GetProgramCounter() += kInstructionSize;
    }


    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::ADDI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class SLTI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 < imm;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 2);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SLTI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class SLTIU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        uint32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 < imm;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 3);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SLTIU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = UnorderedBitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class XORI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 ^ imm;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 4);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::XORI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class ORI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 | imm;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 6);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::ORI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class ANDI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t imm;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], imm);

        rd = rs1 & imm;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t imm;
        ParseNumber(operands[2], imm);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 7);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, imm);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::ANDI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 12);
    }
};

class SLLI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        int32_t shamt;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], shamt);

        std::cout << rs1 << ' ';

        rd = (int32_t)(rs1 << shamt);

        std::cout << rd << '\n';

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t shamt;
        ParseNumber(operands[2], shamt);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, shamt);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SLLI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 24), 5);
    }
};

class SRLI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t shamt;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], shamt);

        rd = rs1 >> shamt;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t shamt;
        ParseNumber(operands[2], shamt);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, shamt);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SRLI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 24), 5);
    }
};

class SRAI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t shamt;
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], shamt);

        rd = rs1 >> shamt;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t shamt;
        ParseNumber(operands[2], shamt);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 4);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, shamt);
        SetBits(bin_command, 27, 31, 8);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SRAI;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 24), 5);
    }
};

class ADD : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 + rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::ADD;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SUB : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 - rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 8);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SUB;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SLL : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 << rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SLL;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SLT : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 < rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 2);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SLT;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SLTU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        uint32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 < rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 3);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override  {
        command = OperationCode::SLTU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class XOR : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 ^ rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 4);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::XOR;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SRL : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 >> rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SRL;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class SRA : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 >> rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 8);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SRA;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class OR : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 | rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 6);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::OR;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class AND : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 & rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 7);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::AND;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class FENCE : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 2);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        int32_t pred;
        ParseNumber(operands[0], pred);

        int32_t succ;
        ParseNumber(operands[1], succ);

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 3);
        SetBits(bin_command, 7, 11, 0);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, 0);
        SetBits(bin_command, 20, 23, pred);
        SetBits(bin_command, 24, 27, succ);
        SetBits(bin_command, 28, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::FENCE;
        operands.resize(2);
        operands[0] = bin_to_string_register[GetBits(bin_command, 20, 23)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 24, 27)];
    }
};

class ECALL : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 0);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 28);
        SetBits(bin_command, 7, 11, 0);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, 0);
        SetBits(bin_command, 20, 24, 0);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::ECALL;
    }
};

class EBREAK : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 0);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 28);
        SetBits(bin_command, 7, 11, 0);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, 0);
        SetBits(bin_command, 20, 24, 1);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::EBREAK;
    }
};

class WFI : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 0);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 28);
        SetBits(bin_command, 7, 11, 0);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, 0);
        SetBits(bin_command, 20, 24, 5);
        SetBits(bin_command, 25, 26, 0);
        SetBits(bin_command, 27, 31, 2);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::WFI;
    }
};

class LB : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Load((*string_to_register_number.find(operands[0])).second, rs1 + offset);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 0);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
    command = OperationCode::LB;
    operands.resize(3);
    operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
    operands[1] = BitsToString(GetBits(bin_command, 20, 31), 12);
    operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
}
};

class LH : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Load((*string_to_register_number.find(operands[0])).second, rs1 + offset, 2);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 0);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::LH;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = BitsToString(GetBits(bin_command, 20, 31), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class LW : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Load((*string_to_register_number.find(operands[0])).second, rs1 + offset, 4);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 0);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 2);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::LW;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = BitsToString(GetBits(bin_command, 20, 31), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class LBU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        uint32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.LoadUnordered((*string_to_register_number.find(operands[0])).second, rs1 + offset);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 0);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 4);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::LBU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = BitsToString(GetBits(bin_command, 20, 31), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class LHU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        uint32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.LoadUnordered((*string_to_register_number.find(operands[0])).second, rs1 + offset, 2);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 0);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::LHU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = BitsToString(GetBits(bin_command, 20, 31), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class SB : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Store((*string_to_register_number.find(operands[0])).second, rs1 + offset);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 8);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 24, bin_register[operands[0]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SB;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[1] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class SH : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Store((*string_to_register_number.find(operands[0])).second, rs1 + offset, 2);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 8);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 24, bin_register[operands[0]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SH;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[1] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class SW : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t offset;
        int32_t rs1;
        ParseNumber(operands[1], offset);
        ParseRegister(operands[2], rs1, memory);

        memory.Store((*string_to_register_number.find(operands[0])).second, rs1 + offset, 4);
        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 8);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 2);
        SetBits(bin_command, 15, 19, bin_register[operands[2]]);
        SetBits(bin_command, 20, 24, bin_register[operands[0]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::SW;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[1] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
        operands[2] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    }
};

class JAL : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 2);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t& pc = memory.GetProgramCounter();
        int32_t offset;
        ParseNumber(operands[1], offset);

        rd = (int32_t)pc + kInstructionSize;

        pc += offset;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[1], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 27);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::JAL;
        operands.resize(2);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = BitsToString(GetBits(bin_command, 12, 31), 20);
    }
};

class JALR : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t offset;
        uint32_t& pc = memory.GetProgramCounter();
        ParseRegister(operands[1], rs1, memory);
        ParseNumber(operands[2], offset);

        rd = (int32_t)pc + kInstructionSize;

        pc = rs1 + offset;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 25);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 31, offset);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::JALR;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = BitsToString(GetBits(bin_command, 20, 31), 20);
    }
};

class BEQ : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t rs1;
        int32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 == rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BEQ;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class BNE : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t rs1;
        int32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 != rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BNE;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class BLT : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t rs1;
        int32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 < rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 4);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BLT;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class BGE : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t rs1;
        int32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 >= rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BGE;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class BLTU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        uint32_t rs1;
        uint32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 < rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 6);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BLTU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class BGEU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        uint32_t rs1;
        uint32_t rs2;
        int32_t offset;

        ParseRegister(operands[0], rs1, memory);
        ParseRegister(operands[1], rs2, memory);
        ParseNumber(operands[2], offset);

        if (rs1 >= rs2) {
            memory.GetProgramCounter() += offset;
        } else {
            memory.GetProgramCounter() += kInstructionSize;
        }
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        int32_t offset;
        ParseNumber(operands[2], offset);

        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 24);
        SetBits(bin_command, 7, 11, offset);
        SetBits(bin_command, 12, 14, 7);
        SetBits(bin_command, 15, 19, bin_register[operands[0]]);
        SetBits(bin_command, 20, 24, bin_register[operands[1]]);
        SetBits(bin_command, 25, 31, offset >> 5);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::BGEU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 20, 24)];
        operands[2] = BitsToString((GetBits(bin_command, 25, 31) << 5) + GetBits(bin_command, 7, 11), 12);
    }
};

class MUL : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 * rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 0);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::MUL;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class MULH : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = (int32_t)(((int64_t)rs1 * (int64_t)rs2) >> 32);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 1);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }


    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::MULH;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class MULHSU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        uint32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = (int32_t)(((int64_t)rs1 * (uint64_t)rs2) >> 32);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 2);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::MULHSU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class MULHU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        uint32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = (int32_t)(((uint64_t)rs1 * (uint64_t)rs2) >> 32);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 3);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::MULHU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class DIV : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 / rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 4);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
    command = OperationCode::DIV;
    operands.resize(3);
    operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
    operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
    operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
}
};

class DIVU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        uint32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = (int32_t)(rs1 / rs2);

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 5);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::DIVU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class REM : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        int32_t rs1;
        int32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = rs1 % rs2;

        memory.GetProgramCounter() += kInstructionSize;
    }

    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 6);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::REM;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};

class REMU : public Operation {
public:
    void execute(const std::vector<std::string>& operands, CPUMemory& memory) override {
        check_operands_number(operands, 3);

        int32_t& rd = memory.GetRegister((*string_to_register_number.find(operands[0])).second);
        uint32_t rs1;
        uint32_t rs2;
        ParseRegister(operands[1], rs1, memory);
        ParseRegister(operands[2], rs2, memory);

        rd = (int32_t)(rs1 % rs2);

        memory.GetProgramCounter() += kInstructionSize;
    }


    uint32_t GetBin(const std::vector<std::string>& operands) override {
        uint32_t bin_command = 0;

        SetBits(bin_command, 0, 1, 3);
        SetBits(bin_command, 2, 6, 12);
        SetBits(bin_command, 7, 11, bin_register[operands[0]]);
        SetBits(bin_command, 12, 14, 7);
        SetBits(bin_command, 15, 19, bin_register[operands[1]]);
        SetBits(bin_command, 20, 24, bin_register[operands[2]]);
        SetBits(bin_command, 25, 26, 1);
        SetBits(bin_command, 27, 31, 0);

        return bin_command;
    }

    void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands) override {
        command = OperationCode::REMU;
        operands.resize(3);
        operands[0] = bin_to_string_register[GetBits(bin_command, 7, 11)];
        operands[1] = bin_to_string_register[GetBits(bin_command, 15, 19)];
        operands[2] = bin_to_string_register[GetBits(bin_command, 20, 24)];
    }
};