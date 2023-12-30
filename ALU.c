#include "cpu.h"


/* arithmetic logic unit control unit*/
uint8_t ALU_Control(uint8_t ALUOp, uint8_t opcode) {
    switch (ALUOp)
    {
     /* LW or SW */
    case 0b00: return 0b0010;

     /* BEQ or BNE */
    case 0b01: return 0b0110;

     /* R type */
    case 0b10:
        switch (opcode)
        {
        case ADD:   return 0b0010;
        case ADDU:  return 0b1010;
        case SUB:   return 0b0110;
        case SUBU:  return 0b1110;
        case AND:   return 0b0000;
        case OR:    return 0b0001;
        case NOR:   return 0b1001;
        case SLT:   return 0b0111;
        case SLTU:  return 0b1111;
        case SLL:   return 0b0100;
        case SRL:   return 0b0101;
        }

     /* I type */
    case 0b11:
        switch (opcode)
        {
        case ADDI:  return 0b0010;
        case ADDIU: return 0b1010;
        case ANDI:  return 0b0000;
        case ORI:   return 0b0001;
        case SLTI:  return 0b0111;
        case SLTIU: return 0b1111;
        case LUI:   return 0b1000;
        }
    }
}


/* arithmetic logic unit operaiton */
uint32_t ALU_Operation(uint8_t ALU_Control, uint32_t operand1, uint32_t operand2) {
    switch (ALU_Control)
    {
    case 0b0010: return (long)operand1 + (long)operand2;    // add
    case 0b1010: return operand1 + operand2;                         // addu
    case 0b0110: return (long)operand1 - (long)operand2;     // sub
    case 0b1110: return operand1 - operand2;		                  // subu
    case 0b0000: return operand1 & operand2;		                  // and
    case 0b0001: return operand1 | operand2;		                  // or
    case 0b1001: return ~(operand1 | operand2);		              // nor
    case 0b0111: return (long)operand1 < (long)operand2;    // slt
    case 0b1111: return operand1 < operand2;		                  // sltu
    case 0b0100: return operand1 << operand2;		                  // sll
    case 0b0101: return operand1 >> operand2;		                  // srl
    case 0b1000: return operand2 << 16;			                          // lui
    }
}