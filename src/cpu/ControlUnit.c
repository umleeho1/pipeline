#include "../header/cpu/ControlUnit.h"
#include "../header/cpu/DecodeUnit.h"
#include "../header/cpu/ALUnit.h"
#include "../src/cpu/ControlUnit.c"
#include "../src/cpu/DecodeUnit.c"
#include "../src/cpu/ALUnit.c"

ControlUnit* ControlUnit_create(Memory* memory, Logger* logger) {
    ControlUnit* controlUnit = (ControlUnit*)malloc(sizeof(ControlUnit));
    controlUnit->memory = memory;
    controlUnit->logger = logger;
    controlUnit->registers = Registers_create(32);
    controlUnit->decodeUnit = DecodeUnit_create();
    controlUnit->alu = ALUnit_create();
    return controlUnit;
}

void ControlUnit_destroy(ControlUnit* controlUnit) {
    Registers_destroy(controlUnit->registers);
    DecodeUnit_destroy(controlUnit->decodeUnit);
    ALUnit_destroy(controlUnit->alu);
    free(controlUnit);
}

int ControlUnit_process(ControlUnit* controlUnit) {
    int cycleCount = 0;
    FetchResult ifResult;
    DecodeResult idResult;
    ExecutionResult exResult;
    MemoryAccessResult maResult;
    WriteBackResult wbResult;

    while (controlUnit->registers->pc != -1) {
        cycleCount++;
        ifResult = ControlUnit_fetch(controlUnit->registers->pc, controlUnit->memory);
        idResult = ControlUnit_decode(controlUnit, ifResult);
        exResult = ControlUnit_execute(controlUnit, idResult);
        maResult = ControlUnit_memoryAccess(controlUnit, exResult);
        wbResult = ControlUnit_writeBack(controlUnit, maResult);
        controlUnit->registers->pc = wbResult.nextPc;

        Logger_cycleCount(controlUnit->logger, cycleCount);
        Logger_fetchLog(controlUnit->logger, cycleCount, ifResult);
        Logger_decodeLog(controlUnit->logger, controlUnit->controlSignal, idResult);
        Logger_executeLog(controlUnit->logger, controlUnit->controlSignal, exResult);
        Logger_memoryAccessLog(controlUnit->logger, controlUnit->controlSignal, exResult.aluValue, maResult.readData, exResult.memWriteData);
        Logger_writeBackLog(controlUnit->logger, controlUnit->controlSignal, wbResult);
    }

    return Registers_getRegister(controlUnit->registers, 2);
}

FetchResult ControlUnit_fetch(ControlUnit* controlUnit, int pc, Memory* memory) {
    FetchResult fetchResult;
    fetchResult.pc = pc;
    fetchResult.instruction = Memory_read(memory, pc);
    Registers_setRegister(controlUnit->registers, pc, Registers_getRegister(controlUnit->registers, pc) + 4);
    return fetchResult;
}

DecodeResult ControlUnit_decode(ControlUnit* controlUnit, FetchResult fetchResult) {
    Instruction parsedInst = controlUnit->decodeUnit->parse(Registers_getRegister(controlUnit->registers, fetchResult.pc), fetchResult.instruction);
    controlUnit->controlSignal = controlUnit->decodeUnit->controlSignal(parsedInst.opcode);
    int writeRegister = Mux_mux(controlUnit->controlSignal.regDest, parsedInst.rd, parsedInst.rt);
    writeRegister = Mux_mux(controlUnit->controlSignal.jal, writeRegister, 31);
    DecodeResult decodeResult;
    decodeResult.parsedInst = parsedInst;
    decodeResult.writeRegister = writeRegister;
    return decodeResult;
}

