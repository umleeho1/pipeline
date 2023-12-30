#ifndef LOGGER_H
#define LOGGER_H

#include "../header/cpu/Results.h"

typedef struct LoggingSignal {
    int cycle;
    int fetch;
    int decode;
    int execute;
    int memoryAccess;
    int writeBack;
    int resultInformation;
    long sleepTime;
} LoggingSignal;

typedef struct Logger {
    LoggingSignal loggingSignal;
    int cycleCount;
    int numberOfExecutedMA;
    int numberOfWriteBack;
    int numberOfTakenBranches;
    int executedOpcodes[OPCODE_COUNT];
    int executedOpcodeType[OPCODE_TYPE_COUNT];
    int executedInstructionSet[EXECUTED_INSTRUCTION_SET_SIZE];
} Logger;

Logger* Logger_init(int cycle, int fetch, int decode, int execute, int memoryAccess, int writeBack, int resultInformation, long sleepTime);
void Logger_cycleCount(Logger* logger, int cycleCount);
void Logger_fetchLog(Logger* logger, int cycleCount, FetchResult fetchResult);
void Logger_decodeLog(Logger* logger, ControlSignal controlSignal, DecodeResult result);
void Logger_executeLog(Logger* logger, ControlSignal controlSignal, ExecutionResult result);
void Logger_memoryAccessLog(Logger* logger, ControlSignal controlSignal, int address, int readValue, int writeValue);
void Logger_writeBackLog(Logger* logger, ControlSignal controlSignal, WriteBackResult result);
void Logger_printProcessResult(Logger* logger, int resultValue);
void Logger_printStep(const char* stepName);

#endif
