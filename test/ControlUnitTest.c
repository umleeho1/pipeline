#include <stdio.h>
#include <stdlib.h>

#include "../header/component/Memory.h"
#include "../header/cpu/ControlUnit.h"

int main() {
    const char* path = "sample/simple.bin";
    int expected = 0;
    
    Memory* memory = Memory_load(20000000, path);
    ControlUnit* controlUnit = ControlUnit_create(memory);
    int processResult = ControlUnit_process(controlUnit);
    
    if (processResult == expected) {
        printf("Process result matches the expected value.\n");
    } else {
        printf("Process result does not match the expected value.\n");
    }
    
    ControlUnit_destroy(controlUnit);
    Memory_destroy(memory);
    
    return 0;
}
