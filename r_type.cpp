#include <vector>
#include <cstdint>
#include <iostream>

void handle_r_type(std::uint32_t* registers, std::uint32_t pc, std::vector<uint8_t>& memory, std::uint32_t instruction, bool& need_to_break){
    int funct = instruction & ((1 << 6) - 1);
    if(funct == 0b001100){
        int code = instruction >> 6;
        if(code == 0b0){
            //stop loop
            need_to_break = true;
        } else if(code == 0b1) {
            //print register states;
            for(int i = 0; i < 32; i++){
                std::cout << i << " " << registers[i] << "\n";
            }
            std::cout << pc << " " << pc << "\n";
        } else if(code == 0b100000){
            //ADD
            int rd = instruction >> 11 & 0b11111;
            int rt = instruction >> 16 & 0b11111;
            int rs = instruction >> 21 & 0b11111;

            registers[rd] = registers[rs] + registers[rt];
        } else if(code == 0b100100){
            //AND
            int rd = instruction >> 11 & 0b11111;
            int rt = instruction >> 16 & 0b11111;
            int rs = instruction >> 21 & 0b11111;

            registers[rd] = registers[rs] & registers[rt];
        } else if(code == 0b100010){
            //SUB
            int rd = instruction >> 11 & 0b11111;
            int rt = instruction >> 16 & 0b11111;
            int rs = instruction >> 21 & 0b11111;

            registers[rd] = registers[rs] - registers[rt];
        }else if(code == 0b101010){
            //SLT, Set less than
            int rd = instruction >> 11 & 0b11111;
            int rt = instruction >> 16 & 0b11111;
            int rs = instruction >> 21 & 0b11111;

            registers[rd] = registers[rs] < registers[rt];
        }else if(code == 0b100101){
            //OR
            int rd = instruction >> 11 & 0b11111;
            int rt = instruction >> 16 & 0b11111;
            int rs = instruction >> 21 & 0b11111;

            registers[rd] = registers[rs] | registers[rt];
        }
    }
}