#include "../header/component/Memory.h"


#include <stdio.h>
#include <stdlib.h>

Memory* Memory_load(int size, const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        printf("파일을 열 수 없습니다: %s\n", path);
        return NULL;
    }

    Memory* memory = malloc(sizeof(Memory));
    memory->size = size;
    memory->data = malloc(sizeof(byte) * size);

    byte bytes[2048];
    int address = 0;
    size_t bytesRead;
    while ((bytesRead = fread(bytes, sizeof(byte), 2048, file)) > 0) {
        for (int i = 0; i < bytesRead; i += 4) {
            memory->data[address] = bytes[i + 3];
            memory->data[address + 1] = bytes[i + 2];
            memory->data[address + 2] = bytes[i + 1];
            memory->data[address + 3] = bytes[i];
            address += 4;
        }
    }

    fclose(file);
    return memory;
}

int Memory_read(Memory* memory, int address, int memRead) {
    if (memRead) {
        int i1 = memory->data[address] << 0 & 0x000000FF;
        int i2 = memory->data[address + 1] << 8 & 0x0000FF00;
        int i3 = memory->data[address + 2] << 16 & 0x00FF0000;
        int i4 = memory->data[address + 3] << 24;
        return i4 + i3 + i2 + i1;
    } else {
        return 0;
    }
}

void Memory_write(Memory* memory, int address, int value, int memWrite) {
    if (memWrite) {
        memory->data[address] = value & 0xFF;
        memory->data[address + 1] = (value >> 8) & 0xFF;
        memory->data[address + 2] = (value >> 16) & 0xFF;
        memory->data[address + 3] = (value >> 24) & 0xFF;
    }
}

void Memory_free(Memory* memory) {
    free(memory->data);
    free(memory);
}
