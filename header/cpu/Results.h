#ifndef RESULTS_H
#define RESULTS_H

typedef struct FetchResult {
    int pc;
    int instruction;
} FetchResult;

typedef struct DecodeResult {
    int shiftAmt;
    int immediate;
    int address;
    int readData1;
    int readData2;
    int writeRegister;
} DecodeResult;

typedef struct ExecutionResult {
    int aluValue;
    int memWriteData;
    int writeRegister;
    int nextPc;
} ExecutionResult;

typedef struct MemoryAccessResult {
    int readData;
    int aluValue;
    int writeRegister;
    int nextPc;
} MemoryAccessResult;

typedef struct WriteBackResult {
    int regWrite;
    int writeRegister;
    int writeData;
    int nextPc;
} WriteBackResult;

#endif
