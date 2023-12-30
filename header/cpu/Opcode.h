#ifndef OPCODE_H
#define OPCODE_H

typedef enum {
    ADDI = 0x08,
    ADDIU = 0x09,
    ADDU = 0x21,
    BEQ = 0x04,
    BNE = 0x05,
    J = 0x02,
    JAL = 0x03,
    JR = 0x08,
    LUI = 0x0F,
    LW = 0x23,
    ORI = 0x0D,
    SLT = 0x2A,
    SLTI = 0x0A,
    SLL = 0x00,
    SW = 0x2B,
    SUBU = 0x23
} Opcode;

typedef enum {
    R, I, J
} OpcodeType;

typedef enum {
    ADDITION,
    EQUAL,
    NOT_EQUAL,
    NONE,
    SHIFT_LEFT,
    OR,
    SET_LESS_THAN,
    SUBTRACTION
} AluOp;

typedef struct {
    Opcode code;
    OpcodeType type;
    AluOp operation;
} OpcodeInfo;

OpcodeInfo Opcode_getInfo(Opcode opcode);
Opcode Opcode_of(int instruction);

#endif /* OPCODE_H */
