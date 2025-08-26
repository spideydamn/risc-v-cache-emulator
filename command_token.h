#pragma once

#include <string>
#include <vector>

enum class OperationCode {
    LUI,
    AUIPC,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    FENCE,
    ECALL,
    EBREAK,
    WFI,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,

    MUL,
    MULH,
    MULHSU,
    MULHU,
    DIV,
    DIVU,
    REM,
    REMU,

    NONE
};

struct CommandToken {
    OperationCode command = OperationCode::NONE;
    std::vector<std::string> operands;
    CommandToken() = default;
    CommandToken(OperationCode new_command, const std::vector<std::string>& new_operands) {
        command = new_command;
        operands = new_operands;
    }
};
