#pragma once

#include <iostream>
#include <fstream>

#include "operations.h"

inline std::unordered_map<std::string, OperationCode> operation_codes = {
        {"lui", OperationCode::LUI},
        {"auipc", OperationCode::AUIPC},
        {"addi", OperationCode::ADDI},
        {"slti", OperationCode::SLTI},
        {"sltiu", OperationCode::SLTIU},
        {"xori", OperationCode::XORI},
        {"ori", OperationCode::ORI},
        {"andi", OperationCode::ANDI},
        {"slli", OperationCode::SLLI},
        {"srli", OperationCode::SRLI},
        {"srai", OperationCode::SRAI},
        {"add", OperationCode::ADD},
        {"sub", OperationCode::SUB},
        {"sll", OperationCode::SLL},
        {"slt", OperationCode::SLT},
        {"sltu", OperationCode::SLTU},
        {"xor", OperationCode::XOR},
        {"srl", OperationCode::SRL},
        {"sra", OperationCode::SRA},
        {"or", OperationCode::OR},
        {"and", OperationCode::AND},
        {"fence", OperationCode::FENCE},
        {"ecall", OperationCode::ECALL},
        {"ebreak", OperationCode::EBREAK},
        {"wfi", OperationCode::WFI},
        {"lb", OperationCode::LB},
        {"lh", OperationCode::LH},
        {"lw", OperationCode::LW},
        {"lbu", OperationCode::LBU},
        {"lhu", OperationCode::LHU},
        {"sb", OperationCode::SB},
        {"sh", OperationCode::SH},
        {"sw", OperationCode::SW},
        {"jal", OperationCode::JAL},
        {"jalr", OperationCode::JALR},
        {"beq", OperationCode::BEQ},
        {"bne", OperationCode::BNE},
        {"blt", OperationCode::BLT},
        {"bge", OperationCode::BGE},
        {"bltu", OperationCode::BLTU},
        {"bgeu", OperationCode::BGEU},

        {"mul", OperationCode::MUL},
        {"mulh", OperationCode::MULH},
        {"mulhsu", OperationCode::MULHSU},
        {"mulhu", OperationCode::MULHU},
        {"div", OperationCode::DIV},
        {"divu", OperationCode::DIVU},
        {"rem", OperationCode::REM},
        {"remu", OperationCode::REMU},

        {"LUI", OperationCode::LUI},
        {"AUIPC", OperationCode::AUIPC},
        {"ADDI", OperationCode::ADDI},
        {"SLTI", OperationCode::SLTI},
        {"SLTIU", OperationCode::SLTIU},
        {"XORI", OperationCode::XORI},
        {"ORI", OperationCode::ORI},
        {"ANDI", OperationCode::ANDI},
        {"SLLI", OperationCode::SLLI},
        {"SRLI", OperationCode::SRLI},
        {"SRAI", OperationCode::SRAI},
        {"ADD", OperationCode::ADD},
        {"SUB", OperationCode::SUB},
        {"SLL", OperationCode::SLL},
        {"SLT", OperationCode::SLT},
        {"SLTU", OperationCode::SLTU},
        {"XOR", OperationCode::XOR},
        {"SRL", OperationCode::SRL},
        {"SRA", OperationCode::SRA},
        {"OR", OperationCode::OR},
        {"AND", OperationCode::AND},
        {"FENCE", OperationCode::FENCE},
        {"ECALL", OperationCode::ECALL},
        {"EBRAK", OperationCode::EBREAK},
        {"WFI", OperationCode::WFI},
        {"LB", OperationCode::LB},
        {"LH", OperationCode::LH},
        {"LW", OperationCode::LW},
        {"LBU", OperationCode::LBU},
        {"LHU", OperationCode::LHU},
        {"SB", OperationCode::SB},
        {"SH", OperationCode::SH},
        {"SW", OperationCode::SW},
        {"JAL", OperationCode::JAL},
        {"JALR", OperationCode::JALR},
        {"BEQ", OperationCode::BEQ},
        {"BNE", OperationCode::BNE},
        {"BLT", OperationCode::BLT},
        {"BGE", OperationCode::BGE},
        {"BLTU", OperationCode::BLTU},
        {"BGEU", OperationCode::BGEU},

        {"MUL", OperationCode::MUL},
        {"MULH", OperationCode::MULH},
        {"MULHSU", OperationCode::MULHSU},
        {"MULHU", OperationCode::MULHU},
        {"DIV", OperationCode::DIV},
        {"DIVU", OperationCode::DIVU},
        {"REM", OperationCode::REM},
        {"REMU", OperationCode::REMU},
};

inline std::unordered_map<OperationCode, std::shared_ptr<Operation>> token_to_class = {
        {OperationCode::LUI, std::make_shared<LUI>()},
        {OperationCode::AUIPC, std::make_shared<AUIPC>()},
        {OperationCode::ADDI, std::make_shared<ADDI>()},
        {OperationCode::SLTI, std::make_shared<SLTI>()},
        {OperationCode::SLTIU, std::make_shared<SLTIU>()},
        {OperationCode::XORI, std::make_shared<XORI>()},
        {OperationCode::ORI, std::make_shared<ORI>()},
        {OperationCode::ANDI, std::make_shared<ANDI>()},
        {OperationCode::SLLI, std::make_shared<SLLI>()},
        {OperationCode::SRLI, std::make_shared<SRLI>()},
        {OperationCode::SRAI, std::make_shared<SRAI>()},
        {OperationCode::ADD, std::make_shared<ADD>()},
        {OperationCode::SUB, std::make_shared<SUB>()},
        {OperationCode::SLL, std::make_shared<SLL>()},
        {OperationCode::SLT, std::make_shared<SLT>()},
        {OperationCode::SLTU, std::make_shared<SLTU>()},
        {OperationCode::XOR, std::make_shared<XOR>()},
        {OperationCode::SRL, std::make_shared<SRL>()},
        {OperationCode::SRA, std::make_shared<SRA>()},
        {OperationCode::OR, std::make_shared<OR>()},
        {OperationCode::AND, std::make_shared<AND>()},
        {OperationCode::FENCE, std::make_shared<FENCE>()},
        {OperationCode::ECALL, std::make_shared<ECALL>()},
        {OperationCode::EBREAK, std::make_shared<EBREAK>()},
        {OperationCode::WFI, std::make_shared<WFI>()},
        {OperationCode::LB, std::make_shared<LB>()},
        {OperationCode::LH, std::make_shared<LH>()},
        {OperationCode::LW, std::make_shared<LW>()},
        {OperationCode::LBU, std::make_shared<LBU>()},
        {OperationCode::LHU, std::make_shared<LHU>()},
        {OperationCode::SB, std::make_shared<SB>()},
        {OperationCode::SH, std::make_shared<SH>()},
        {OperationCode::SW, std::make_shared<SW>()},
        {OperationCode::JAL, std::make_shared<JAL>()},
        {OperationCode::JALR, std::make_shared<JALR>()},
        {OperationCode::BEQ, std::make_shared<BEQ>()},
        {OperationCode::BNE, std::make_shared<BNE>()},
        {OperationCode::BLT, std::make_shared<BLT>()},
        {OperationCode::BGE, std::make_shared<BGE>()},
        {OperationCode::BLTU, std::make_shared<BLTU>()},
        {OperationCode::BGEU, std::make_shared<BGEU>()},

        {OperationCode::MUL, std::make_shared<MUL>()},
        {OperationCode::MULH, std::make_shared<MULH>()},
        {OperationCode::MULHSU, std::make_shared<MULHSU>()},
        {OperationCode::MULHU, std::make_shared<MULHU>()},
        {OperationCode::DIV, std::make_shared<DIV>()},
        {OperationCode::DIVU, std::make_shared<DIVU>()},
        {OperationCode::REM, std::make_shared<REM>()},
        {OperationCode::REMU, std::make_shared<REMU>()},
};



class Serializer {
private:
    std::ofstream stream;
public:
    Serializer() = default;

    explicit Serializer(const std::string& file_path) {
        if (this->stream.is_open()) {
            std::cerr << "serializer error\n";
            exit(1);
        }
        this->stream.open(file_path, std::ios::out);
    }

    void execute(const CommandToken& token) {
        if (!this->stream.is_open()) {
            std::cerr << "serializer error\n";
            exit(1);
        }
        uint32_t operation_class = token_to_class[token.command]->GetBin(token.operands);
        stream.write(reinterpret_cast<const char*>(&operation_class), 4);
        
    }

    void close() {
        if (!this->stream.is_open()) {
            std::cerr << "serializer error\n";
            exit(1);
        }
        this->stream.close();
    };
}; 