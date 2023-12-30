#ifndef DECODEUNIT_H
#define DECODEUNIT_H

#include "../header/cpu/Opcode.h"

class ControlSignal {
public:
    ControlSignal(Opcode opcode)
        : opcode(opcode),
          regDest(opcode.getType() == Opcode::Type::R),
          aluSrc((opcode.getType() != Opcode::Type::R)
                 && (opcode != Opcode::BEQ)
                 && (opcode != Opcode::BNE)),
          shift(opcode == Opcode::SLL),
          upperImm(opcode == Opcode::LUI),
          memToReg(opcode == Opcode::LW),
          regWrite((opcode != Opcode::SW)
                    && (opcode != Opcode::BEQ)
                    && (opcode != Opcode::BNE)
                    && (opcode != Opcode::J)
                    && (opcode != Opcode::JR)),
          memRead(opcode == Opcode::LW),
          memWrite(opcode == Opcode::SW),
          jump((opcode == Opcode::J) || (opcode == Opcode::JAL)),
          branch((opcode == Opcode::BNE) || (opcode == Opcode::BEQ)),
          jr(opcode == Opcode::JR),
          jal(opcode == Opcode::JAL),
          aluOp(opcode.getOperation()) {}

private:
    Opcode opcode;
    bool regDest;
    bool aluSrc;
    bool shift;
    bool upperImm;
    bool memToReg;
    bool regWrite;
    bool memRead;
    bool memWrite;
    bool jump;
    bool branch;
    bool jr;
    bool jal;
    AluOp aluOp;
};

class ParsedInstruction {
public:
    ParsedInstruction(int pc, int instruction)
        : pc(pc),
          instruction(instruction),
          opcode(Opcode::of(instruction)),
          rs(instruction >> 21 & 0x1F),
          rt(instruction >> 16 & 0x1F),
          rd(instruction >> 11 & 0x1F),
          shiftAmt(instruction >> 6 & 0x1F),
          immediate(immediate(pc, instruction)),
          address(address(pc, instruction)) {}

private:
    int pc;
    int instruction;
    Opcode opcode;
    int rs;
    int rt;
    int rd;
    int shiftAmt;
    int immediate;
    int address;

    static int immediate(int pc, int instruction) {
        int originImm = instruction & 0xFFFF;
        switch (Opcode::of(instruction)) {
            case Opcode::ADDIU:
            case Opcode::ADDI:
            case Opcode::SLTI:
            case Opcode::SW:
            case Opcode::LW:
                return signExtension32(originImm);
            case Opcode::ORI:
                return zeroExtension32(originImm);
            case Opcode::BNE:
            case Opcode::BEQ:
                return pc + branchAddress(originImm);
            default:
                return originImm;
        }
    }

    static int address(int pc, int instruction) {
        int originAddress = instruction & 0x3FFFFFF;
        switch (Opcode::of(instruction)) {
            case Opcode::J:
            case Opcode::JAL:
                return jumpAddress(pc, originAddress);
            default:
                return originAddress;
        }
    }
};

ParsedInstruction DecodeUnit_parse(int pc, int instruction);
ControlSignal DecodeUnit_controlSignal(Opcode opcode);

#endif /* DECODEUNIT_H */
