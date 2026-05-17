#include <cstdint>
#include <vector>
#include <iostream>

void addi(std::uint32_t* registers, std::uint32_t pc, std::vector<uint8_t>& memory, std::uint32_t instruction){
    //gets immediate value
    std::int16_t immediate_value = instruction & ((1 << 16) - 1);
    //gets source register
    int rs = instruction >> 21 & 0b11111;
    //gets target register
    int rt = instruction >> 16 & 0b11111;
    //does operation if rt is not 0, which is constant 0
    if(rt != 0){
        registers[rt] = registers[rs] + immediate_value;
    }
}

void andi(std::uint32_t* registers, std::uint32_t pc, std::vector<uint8_t>& memory, std::uint32_t instruction){
    std::int16_t immediate_value = instruction & ((1 << 16) - 1);
    int rs = instruction >> 21 & 0b11111;
    int rt = instruction >> 16 & 0b11111;
    if(rt != 0){
        registers[rt] = registers[rs] & immediate_value;
    }
}

void lw(std::uint32_t* registers, std::uint32_t pc, std::vector<uint8_t>& memory, std::uint32_t instruction){
    std::int16_t offset = instruction & ((1 << 16) - 1);
    std::int32_t base = registers[(instruction >> 21) & ((1 << 5) - 1)];
    int rt = (instruction >> 16) & ((1 << 5) - 1);

    if ((offset + base) % 4 != 0) {
        std::cout << "ERROR: Memory location needs to be multiple of 4 to be aligned\n";
    }
    registers[rt] = (memory[offset + base] << 24) | (memory[offset + base + 1] << 16) | (memory[offset + base + 2] << 8) | (memory[offset + base + 3]);
}

void sw(std::uint32_t* registers, std::uint32_t pc, std::vector<uint8_t>& memory, std::uint32_t instruction){
    std::int16_t offset = instruction & ((1 << 16) - 1);
    std::int32_t base = registers[(instruction >> 21) & ((1 << 5) - 1)];
    int rt = (instruction >> 16) & ((1 << 5) - 1);

    if ((offset + base) % 4 != 0) {
        std::cout << "ERROR: Memory location needs to be multiple of 4 to be aligned\n";
    }
    std::uint8_t first = registers[rt] >> 24;
    std::uint8_t second = registers[rt] >> 16 & 0xFF;
    std::uint8_t third = registers[rt] >> 8 & 0xFF;
    std::uint8_t fourth = registers[rt] & 0xFF;

    memory[offset + base] = first;
    memory[offset + base + 1] = second;
    memory[offset + base + 2] = third;
    memory[offset + base + 3] = fourth;
}

void beq(std::uint32_t* registers, std::uint32_t& pc, std::vector<uint8_t>& memory, std::uint32_t instruction, bool& need_to_continue){
    int rt = (instruction >> 16) & 0b11111;
    int rs = (instruction >> 21) & 0b11111;
    std::int16_t offset = instruction & 0xFFFF;
    if(registers[rt] == registers[rs]){
        pc = (pc + 4) + ((std::int32_t)offset << 2);
        need_to_continue = true;
    }
}

void bne(std::uint32_t* registers, std::uint32_t& pc, std::vector<uint8_t>& memory, std::uint32_t instruction, bool& need_to_continue){
    int rt = (instruction >> 16) & 0b11111;
    int rs = (instruction >> 21) & 0b11111;
    std::int16_t offset = instruction & 0xFFFF;
    if(registers[rt] != registers[rs]){
        pc = (pc + 4) + ((std::int32_t)offset << 2);
        need_to_continue = true;
    }
}