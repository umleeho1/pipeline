#include "cpu.h"


/* initialize the registers */
void RF_Init() {
    Register[sp] = 0x1000000;
    Register[ra] = 0xffffffff;
}


/* read data from the registers */
void RF_Read(uint8_t RdReg1, uint8_t RdReg2) {
    IDEX[0].ReadData1 = Register[RdReg1];
    IDEX[0].ReadData2 = Register[RdReg2];
}


/* write data into the registers */
void RF_Write(uint8_t WrtReg, uint32_t WrtData, bool WrtEnable) {
    if ((WrtReg > 0) && (WrtEnable == true)) {
        register_operation++;
        Register[WrtReg] = WrtData;
    }
}