#include "../header/cpu/DecodeUnit.h"
#include "../header/cpu/Opcode.h"
#include "../src/cpu/DecodeUnit.c"
#include "../src/cpu/Opcode.c"


ParsedInstruction DecodeUnit_parse(int pc, int instruction) {
    ParsedInstruction parsedInst;
    parsedInst.pc = pc;
    parsedInst.instruction = instruction;
    parsedInst.opcode = Opcode_of(instruction);
    parsedInst.rs = (instruction >> 21) & 0x1F;
    parsedInst.rt = (instruction >> 16) & 0x1F;
    parsedInst.rd = (instruction >> 11) & 0x1F;
    parsedInst.shiftAmt = (instruction >> 6) & 0x1F;
    parsedInst.immediate = DecodeUnit_immediate(pc, instruction);
    parsedInst.address = DecodeUnit_address(pc, instruction);
    return parsedInst;
}

ControlSignal DecodeUnit_controlSignal(Opcode opcode) {
    ControlSignal controlSignal;
    controlSignal.opcode = opcode;
    controlSignal.regDest = opcode.type == R_TYPE;
    controlSignal.aluSrc = (opcode.type != R_TYPE) && (opcode != BEQ) && (opcode != BNE);
    controlSignal.shift = opcode == SLL;
    controlSignal.upperImm = opcode == LUI;
    controlSignal.memToReg = opcode == LW;
    controlSignal.regWrite = (opcode != SW) && (opcode != BEQ) && (opcode != BNE) && (opcode != J) && (opcode != JR);
    controlSignal.memRead = opcode == LW;
    controlSignal.memWrite = opcode == SW;
    controlSignal.jump = (opcode == J) || (opcode == JAL);
    controlSignal.branch = (opcode == BNE) || (opcode == BEQ);
    controlSignal.jr = opcode == JR;
    controlSignal.jal = opcode == JAL;
    controlSignal.aluOp = opcode.operation;
    return controlSignal;
}
