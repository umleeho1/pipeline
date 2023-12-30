#include "../header/cpu/Opcode.h"

OpcodeInfo Opcode_getInfo(Opcode opcode) {
    OpcodeInfo info;
    switch (opcode) {
        case Opcode::ADDI:
            info.code = Opcode::ADDI;
            info.type = Opcode::I;
            info.operation = Operation::ADDITION;
            break;
        case Opcode::ADDIU:
            info.code = Opcode::ADDIU;
            info.type = Opcode::I;
            info.operation = Operation::ADDITION;
            break;
        case Opcode::ADDU:
            info.code = Opcode::ADDU;
            info.type = Opcode::R;
            info.operation = Operation::ADDITION;
            break;
        case Opcode::BEQ:
            info.code = Opcode::BEQ;
            info.type = Opcode::I;
            info.operation = Operation::EQUAL;
            break;
        case Opcode::BNE:
            info.code = Opcode::BNE;
            info.type = Opcode::I;
            info.operation = Operation::NOT_EQUAL;
            break;
        case Opcode::J:
            info.code = Opcode::J;
            info.type = Opcode::J;
            info.operation = Operation::NONE;
            break;
        case Opcode::JAL:
            info.code = Opcode::JAL;
            info.type = Opcode::J;
            info.operation = Operation::NONE;
            break;
        case Opcode::JR:
            info.code = Opcode::JR;
            info.type = Opcode::R;
            info.operation = Operation::NONE;
            break;
        case Opcode::LUI:
            info.code = Opcode::LUI;
            info.type = Opcode::I;
            info.operation = Operation::SHIFT_LEFT;
            break;
        case Opcode::LW:
            info.code = Opcode::LW;
            info.type = Opcode::I;
            info.operation = Operation::ADDITION;
            break;
        case Opcode::ORI:
            info.code = Opcode::ORI;
            info.type = Opcode::I;
            info.operation = Operation::OR;
            break;
        case Opcode::SLT:
            info.code = Opcode::SLT;
            info.type = Opcode::R;
            info.operation = Operation::SET_LESS_THAN;
            break;
        case Opcode::SLTI:
            info.code = Opcode::SLTI;
            info.type = Opcode::I;
            info.operation = Operation::SET_LESS_THAN;
            break;
        case Opcode::SLL:
            info.code = Opcode::SLL;
            info.type = Opcode::R;
            info.operation = Operation::SHIFT_LEFT;
            break;
        case Opcode::SW:
            info.code = Opcode::SW;
            info.type = Opcode::I;
            info.operation = Operation::ADDITION;
            break;
        case Opcode::SUBU:
            info.code = Opcode::SUBU;
            info.type = Opcode::R;
            info.operation = Operation::SUBTRACTION;
            break;
        // 추가적인 case 문이 필요한 경우 여기에 추가해주세요.
        default:
            // 알 수 없는 opcode에 대한 처리를 여기에 추가해주세요.
            break;
    }
    return info;
}
