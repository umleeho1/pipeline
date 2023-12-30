#include "../header/component/Registers.h"

#include <stdlib.h>

Registers* createRegisters(int size) {
    Registers* registers = malloc(sizeof(Registers));

    registers->registerSize = (size < 32) ? 32 : size;
    registers->r = malloc(registers->registerSize * sizeof(int));

    for (int i = 0; i < registers->registerSize; i++) {
        registers->r[i] = 0;
    }

    registers->r[29] = 0x1000000;
    registers->r[31] = -1;
    registers->pc = 0;

    return registers;
}

void destroyRegisters(Registers* registers) {
    free(registers->r);
    free(registers);
}

int getRegisterValue(Registers* registers, int registerIndex) {
    return registers->r[registerIndex];
}

void writeRegister(Registers* registers, int regWrite, int writeRegister, int writeData) {
    if (regWrite) {
        registers->r[writeRegister] = writeData;
    }
}
