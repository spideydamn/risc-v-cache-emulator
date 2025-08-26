#pragma once

#include <fstream>
#include <vector>

#include "deserializer.h"

inline std::pair<std::string, std::vector<std::string>> ParseLine(const std::string& line) {
    std::pair<std::string, std::vector<std::string>> parsed_line = {"", std::vector<std::string>{}};
    bool is_opcode = true;
    bool is_comment = false;
    uint8_t operand_number = 0;
    char c;
    for (int i = 0; i < line.size(); ++i) {
        c = line[i];
        if (i + 1 < line.size() && c == '/' && line[i + 1] == '/') {
            is_opcode = false;
            is_comment = true;
        } else if (is_opcode && isalpha(c)) {
            parsed_line.first += c;
        } else if (is_opcode && (c == ' ' || c == '\t')) {
            is_opcode = false;
            parsed_line.second.emplace_back("");
            if (operation_codes.find(parsed_line.first) == operation_codes.end()) {
                std::cerr << "parser error";
                exit(1);
            }
        } else if (!is_opcode && !is_comment && c != ',' && c != ' ' && c != '\t') {
            parsed_line.second[operand_number] += c;
        } else if (!is_opcode && !is_comment && c == ',') {
            if (string_to_register_number.find(parsed_line.second[operand_number]) == string_to_register_number.end() && !is_number( parsed_line.second[operand_number])) {
                std::cerr << "parser error";
                exit(1);
            }
            ++operand_number;
            parsed_line.second.emplace_back("");
        } else if (c != ' ' && c != '\t' && !is_comment) {
            std::cerr << "parser error";
            exit(1);
        }
    }
    return parsed_line;
}

inline CommandToken ConvertStringToToken(const std::pair<std::string, std::vector<std::string>>& string_data) {
    OperationCode command = operation_codes[string_data.first];
    std::vector<std::string> operands = string_data.second;
    CommandToken result(command, operands);
    return result;
}

class Parser {
public:
    static void ReadFile(const std::string& read_path, const std::string& write_path) {
        Serializer serializer = Serializer(write_path);
        std::ifstream read_file = std::ifstream(read_path);
        std::string line;
        std::pair<std::string, std::vector<std::string>> parsed_line;

        while (std::getline(read_file, line)) {
            parsed_line = ParseLine(line);
            serializer.execute(ConvertStringToToken(parsed_line));
        }

        read_file.close();
        serializer.close();
    }
};