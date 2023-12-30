#include "cpu.h"


/* initialize variables in control unit */
void CU_Init() {
    Jump = 0;             
    SignEx = 0;          
    memset(&IDEX[0].Control, 0, sizeof(IDEX_SIG));
}


/* control unit operation */
void CU_Operation(uint8_t opcode, uint32_t funct) {
    Jump = (opcode == J) || (opcode == JAL);
    IDEX[0].Control.RegDst = (opcode == 0x00);
    SignEx = (opcode != ANDI) && (opcode != ORI);
    IDEX[0].Control.Shift = (opcode == 0x00) && ((funct == SLL) || (funct == SRL));
    IDEX[0].Control.ALUSrc = (opcode != 0x00) && (opcode != BEQ) && (opcode != BNE);
    IDEX[0].Control.MemToReg = (opcode == LW);
    IDEX[0].Control.RegWrite = (opcode != SW) && (opcode != BEQ) && (opcode != BNE) && (opcode != J) && !((opcode == 0x00) && (funct == JR));
    IDEX[0].Control.MemRead = (opcode == LW);
    IDEX[0].Control.MemWrite = (opcode == SW);
    IDEX[0].Control.Branch = (opcode == BEQ) || (opcode == BNE);
    IDEX[0].Control.JumpReg = ((opcode == 0x00) && (funct == JR)) || ((opcode == 0x00) && (funct == JALR));
    IDEX[0].Control.JumpLink = (opcode == JAL) || ((opcode == 0x00) && (funct == JALR));
    IDEX[0].Control.Rtype = (opcode == 0x00);
    IDEX[0].Control.Equal = (opcode == BEQ);
    IDEX[0].Control.ReAddr = (opcode == JAL);

   /* load type*/
    if ((opcode == LW) || (opcode == LL) || (opcode == LHU) || (opcode == LBU))
        IDEX[0].Control.ALUOp = 0b00;
    /* store type*/
    else if ((opcode == SW) || (opcode == SH) || (opcode == SC) || (opcode == SB))
        IDEX[0].Control.ALUOp = 0b00;
   /* branch type*/
    else if ((opcode == BEQ) || (opcode == BNE))
        IDEX[0].Control.ALUOp = 0b01;
    /* R type */
    else if (opcode == 0x00)
        IDEX[0].Control.ALUOp = 0b10;
    /* I type */
    else
        IDEX[0].Control.ALUOp = 0b11;
}