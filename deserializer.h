 #pragma once

#include <iostream>
#include <fstream>
#include <cstdint>

#include "serializer.h"


inline uint32_t CheckBits(uint32_t command, uint8_t left, uint8_t right) {
    uint32_t num = 0;
    for (uint8_t i = right; i >= left; --i) {
        num <<= 1;
        num |= (command >> i) & (uint32_t)1;
    }
    return num;
}

inline CommandToken ParseBin(uint32_t bin_command) {
    CommandToken token;
    switch (CheckBits(bin_command, 2, 6)) {
        case 13:
            token_to_class[OperationCode::LUI]->ParseBin(bin_command, token.command, token.operands);
            break;
        case 5:
            token_to_class[OperationCode::AUIPC]->ParseBin(bin_command, token.command, token.operands);
            break;
        case 4:
            switch (CheckBits(bin_command, 12, 14)) {
                case 0:
                    token_to_class[OperationCode::ADDI]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 1:
                    token_to_class[OperationCode::SLLI]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 2:
                    token_to_class[OperationCode::SLTI]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 3:
                    token_to_class[OperationCode::SLTIU]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 4:
                    token_to_class[OperationCode::XORI]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 5:
                    switch (CheckBits(bin_command, 27, 31)) {
                        case 0:
                            token_to_class[OperationCode::SRLI]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 8:
                            token_to_class[OperationCode::SRAI]->ParseBin(bin_command, token.command, token.operands);
                            break;
                    }
                    break;
                case 6:
                    token_to_class[OperationCode::ORI]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 7:
                    token_to_class[OperationCode::ANDI]->ParseBin(bin_command, token.command, token.operands);
                    break;
            }
            break;
        case 12:
            switch (CheckBits(bin_command, 25, 26)) {
                case 0:
                    switch (CheckBits(bin_command, 12, 14)) {
                        case 0:
                            switch (CheckBits(bin_command, 27, 31)) {
                                case 0:
                                    token_to_class[OperationCode::ADD]->ParseBin(bin_command, token.command, token.operands);
                                    break;
                                case 8:
                                    token_to_class[OperationCode::SUB]->ParseBin(bin_command, token.command, token.operands);
                                    break;
                            }
                            break;
                        case 1:
                            token_to_class[OperationCode::SLL]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 2:
                            token_to_class[OperationCode::SLT]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 3:
                            token_to_class[OperationCode::SLTU]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 4:
                            token_to_class[OperationCode::XOR]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 5:
                            switch (CheckBits(bin_command, 27, 31)) {
                                case 0:
                                    token_to_class[OperationCode::SRL]->ParseBin(bin_command, token.command, token.operands);
                                    break;
                                case 8:
                                    token_to_class[OperationCode::SRA]->ParseBin(bin_command, token.command, token.operands);
                                    break;
                            }
                            break;
                        case 6:
                            token_to_class[OperationCode::OR]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 7:
                            token_to_class[OperationCode::AND]->ParseBin(bin_command, token.command, token.operands);
                            break;
                    }
                    break;
                case 1:
                    switch (CheckBits(bin_command, 12, 14)) {
                        case 0:
                            token_to_class[OperationCode::MUL]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 1:
                            token_to_class[OperationCode::MULH]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 2:
                            token_to_class[OperationCode::MULHSU]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 3:
                            token_to_class[OperationCode::MULHU]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 4:
                            token_to_class[OperationCode::DIV]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 5:
                            token_to_class[OperationCode::DIVU]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 6:
                            token_to_class[OperationCode::REM]->ParseBin(bin_command, token.command, token.operands);
                            break;
                        case 7:
                            token_to_class[OperationCode::REMU]->ParseBin(bin_command, token.command, token.operands);
                            break;
                    }
                    break;
            }
            break;
        case 3:
            token_to_class[OperationCode::FENCE]->ParseBin(bin_command, token.command, token.operands);
            break;
        case 28:
            switch (CheckBits(bin_command, 20, 24)) {
                case 0:
                    token_to_class[OperationCode::ECALL]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 1:
                    token_to_class[OperationCode::EBREAK]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 5:
                    token_to_class[OperationCode::WFI]->ParseBin(bin_command, token.command, token.operands);
                    break;
            }
            break;
        case 0:
            switch (CheckBits(bin_command, 12, 14)) {
                case 0:
                    token_to_class[OperationCode::LB]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 1:
                    token_to_class[OperationCode::LH]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 2:
                    token_to_class[OperationCode::LW]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 4:
                    token_to_class[OperationCode::LBU]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 5:
                    token_to_class[OperationCode::LHU]->ParseBin(bin_command, token.command, token.operands);
                    break;
            }
            break;
        case 8:
            switch (CheckBits(bin_command, 12, 14)) {
                case 0:
                    token_to_class[OperationCode::SB]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 1:
                    token_to_class[OperationCode::SH]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 2:
                    token_to_class[OperationCode::SW]->ParseBin(bin_command, token.command, token.operands);
                    break;
            }
            break;
        case 27:
            token_to_class[OperationCode::JAL]->ParseBin(bin_command, token.command, token.operands);
            break;
        case 25:
            token_to_class[OperationCode::JALR]->ParseBin(bin_command, token.command, token.operands);
            break;
        case 24:
            switch (CheckBits(bin_command, 12, 14)) {
                case 0:
                    token_to_class[OperationCode::BEQ]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 1:
                    token_to_class[OperationCode::BNE]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 4:
                    token_to_class[OperationCode::BLT]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 5:
                    token_to_class[OperationCode::BGE]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 6:
                    token_to_class[OperationCode::BLTU]->ParseBin(bin_command, token.command, token.operands);
                    break;
                case 7:
                    token_to_class[OperationCode::BGEU]->ParseBin(bin_command, token.command, token.operands);
                    break;
            }
            break;
    }
    return token;
}

class Deserializer {
private:
    std::ifstream stream;
    std::string path;
public:
    explicit Deserializer(const std::string& file_path) {
        path = file_path;
    };

    CommandToken execute() {
        if (!stream.is_open()) {
            stream.open(path, std::ios::in);
        }

        uint32_t bin_command;
        if (!stream.read(reinterpret_cast<char *>(&bin_command), 4)) {
            return {};
        }

        return ParseBin(bin_command);
    }
};
