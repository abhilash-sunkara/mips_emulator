#include <vector>
#include <cstdint>
#include <iostream>
#include "j_type.cpp"
#include "i_type.cpp"
#include "r_type.cpp"

void add_instruction_to_memory(std::vector<uint8_t>& memory, std::uint32_t instruction, int location){
    std::uint8_t first = instruction >> 24;
    std::uint8_t second = instruction >> 16 & 0b11111111;
    std::uint8_t third = instruction >> 8 & 0b11111111;
    std::uint8_t fourth = instruction & 0b11111111;

    memory[location] = first;
    memory[location+1] = second;
    memory[location+2] = third;
    memory[location+3] = fourth;
}

int main(){
    std::uint32_t registers[32] = {};
    registers[0] = 0;
    std::uint32_t pc = 0;

    std::vector<uint8_t> memory(0x100000);

    //adds instructions to memory
    //at some point or other I should change this to be more intuitive and split up the fields
    add_instruction_to_memory(memory, 0b00100001000010000000000000000111, 0);
    add_instruction_to_memory(memory, 0b00000000000000000000000001001100, 4);

    //save to memory
    //101011 01000 01000 0000000000100001

    add_instruction_to_memory(memory, 0b10101101000010000000000000100001, 8);

    //load from memory
    //100011 00100 00101 0000000000100001
    add_instruction_to_memory(memory, 0b10001101000010010000000000100001, 12);

    //should see value 7 in 8 and 9 registers now
    
    add_instruction_to_memory(memory, 0b00000000000000000000000001001100, 16);

    add_instruction_to_memory(memory, 0b00000000000000000000000000001100, 20);


    //adds some instructions to instructions here 
    //pc loads at 0 and keeps incrementing by 4
    //when instruction loaded is "syscall" program is terminated

    while(true){
        std::uint32_t instruction = memory[pc] << 24 | memory[pc+1] << 16 | memory[pc+2] << 8 | memory[pc+3];

        int opcode = instruction >> 26;
        bool need_to_break = false;
        bool need_to_continue = false;

        switch (opcode) {
            case 0x00: handle_r_type(registers, pc, memory, instruction, need_to_break); break;
            case 0x02: handle_j_type(registers, pc, memory, instruction, need_to_continue); break;
            case 0x03: jal(registers, pc, memory, instruction, need_to_continue); break;
            case 0x04: beq(registers, pc, memory, instruction, need_to_continue); break;
            case 0x05: bne(registers, pc, memory, instruction, need_to_continue); break;
            case 0x08: addi(registers, pc, memory, instruction); break;
            case 0x09: andi(registers, pc, memory, instruction); break;
            case 0x23: lw(registers, pc, memory, instruction); break;
            case 0x2B: sw(registers, pc, memory, instruction); break;
        }

        if(need_to_break){
            break;
        }
        if(need_to_continue){
            continue;
        }

        pc += 4;
    }
}
