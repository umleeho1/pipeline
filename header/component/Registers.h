#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct {
    int registerSize;
    int* r;
    int pc;
} Registers;

Registers* createRegisters(int size);
void destroyRegisters(Registers* registers);
int getRegisterValue(Registers* registers, int registerIndex);
void writeRegister(Registers* registers, int regWrite, int writeRegister, int writeData);

#endif
