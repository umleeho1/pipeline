#include <stdio.h>
#include <stdlib.h>
#include "../header/utils/Logger.h"

Logger* Logger_init(int cycle, int fetch, int decode, int execute, int memoryAccess, int writeBack, int resultInformation, long sleepTime) {
    Logger* logger = (Logger*)malloc(sizeof(Logger));
    logger->loggingSignal.cycle = cycle;
    logger->loggingSignal.fetch = fetch;
    logger->loggingSignal.decode = decode;
    logger->loggingSignal.execute = execute;
    logger->loggingSignal.memoryAccess = memoryAccess;
    logger->loggingSignal.writeBack = writeBack;
    logger->loggingSignal.resultInformation = resultInformation;
    logger->loggingSignal.sleepTime = sleepTime;
    logger->cycleCount = 0;
    logger->numberOfExecutedMA = 0;
    logger->numberOfWriteBack = 0;
    logger->numberOfTakenBranches = 0;
    for (int i = 0; i < OPCODE_COUNT; i++) {
        logger->executedOpcodes[i] = 0;
    }
    for (int i = 0; i < OPCODE_TYPE_COUNT; i++) {
        logger->executedOpcodeType[i] = 0;
    }
    for (int i = 0; i < EXECUTED_INSTRUCTION_SET_SIZE; i++) {
        logger->executedInstructionSet[i] = 0;
    }
    return logger;
}

void Logger_cycleCount(Logger* logger, int cycleCount) {
    logger->cycleCount = cycleCount;

    if (!logger->loggingSignal.cycle) return;
    if (logger->cycleCount % 1000000 == 0) {
        printf("cycle : %d\n", logger->cycleCount);
    }
}

void Logger_fetchLog(Logger* logger, int cycleCount, FetchResult fetchResult) {
    logger->executedInstructionSet[fetchResult.instruction] = 1;

    if (!logger->loggingSignal.fetch) return;

    Logger_printStep("IF");
    printf("cyl : %d, pc : 0x%02X, instruction : 0x%08X\n",
           cycleCount, fetchResult.pc, fetchResult.instruction);
}
