#include <stdio.h>
#include "../header/component/Memory.h"
#include "../header/cpu/ControlUnit.h"
#include "../header/utils/Logger.h"
#include "../src/component/Memory.c"
#include "../src/utils/Logger.c"
#include "../src/cpu/ControlUnit.c"

int main() {
    Logger logger = initLogger();
    const char* fileToLoad = "HW2/input4/input.bin";
    Memory memory = Memory_load(20000000, fileToLoad);

    ControlUnit controlUnit;
    initControlUnit(&controlUnit, &memory, &logger);
    int processResult = process(&controlUnit);

    printProcessResult(&logger, processResult);

    return 0;
}

Logger initLogger() {
    Logger logger;
    logger.cycle = 1;
    logger.fetch = 1;
    logger.decode = 1;
    logger.execute = 1;
    logger.memoryAccess = 1;
    logger.writeBack = 1;
    logger.resultInformation = 1;
    logger.sleepTime = 0;

    return logger;
}
