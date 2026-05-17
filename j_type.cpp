#include <cstdint>
#include <vector>

void handle_j_type(std::uint32_t* registers, std::uint32_t& pc, std::vector<uint8_t>& memory, std::uint32_t instruction, bool& need_to_continue){
    //bitwise ands to keep only last 26 bits
    int location = instruction & ((1 << 26) - 1);
    //shifts forward by 2
    location = location << 2;
    //gets first 4 bits of pc
    int pc_code = (pc + 4) & 0xF0000000;
    //bitwise ors to combine pc_code and location
    location = pc_code | location;
    pc = location;
    need_to_continue = true;
}

void jal(std::uint32_t* registers, std::uint32_t& pc, std::vector<uint8_t>& memory, std::uint32_t instruction, bool& need_to_continue){
    //bitwise ands to keep only last 26 bits
    int location = instruction & ((1 << 26) - 1);
    //shifts forward by 2
    location = location << 2;
    //gets first 4 bits of pc
    int pc_code = (pc + 4) & 0xF0000000;
    registers[31] = pc + 4;
    //bitwise ors to combine pc_code and location
    location = pc_code | location;
    pc = location;
    need_to_continue = true;
}