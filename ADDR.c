#include "cpu.h"


/* sign extended */
uint32_t SignExtend(uint16_t immediate) {
    if (!(immediate & 0x8000)) return 0x0000ffff & immediate;
    else return 0xffff0000 | immediate;
}

/* zero extended */
uint32_t ZeroExtend(uint16_t immediate) {
    return 0x0000ffff & immediate;
}

/* branch addr */
uint32_t BranchAddr(uint32_t PC, uint32_t immediate) {
    return PC + (immediate << 2);
}

/* jump addr */
uint32_t JumpAddr(uint32_t PC, uint32_t address) {
    return (PC & 0xf0000000) | (address << 2);
}

/*PC addr  */
uint32_t PCAddr(uint32_t PC) {
    return PC + 4;
}