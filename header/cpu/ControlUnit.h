#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "../header/component/Memory.h"
#include "../header/utils/Logger.h"

typedef struct {
    Memory* memory;
    Logger* logger;
    Registers* registers;
    DecodeUnit* decodeUnit;
    ALUnit* alu;
    ControlSignal controlSignal;
} ControlUnit;

ControlUnit* ControlUnit_create(Memory* memory, Logger* logger);
void ControlUnit_destroy(ControlUnit* controlUnit);
int ControlUnit_process(ControlUnit* controlUnit);

#endif /* CONTROLUNIT_H */
