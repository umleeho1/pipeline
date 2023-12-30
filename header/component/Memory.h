#ifndef MEMORY_H
#define MEMORY_H

typedef unsigned char byte;

typedef struct Memory {
    int size;
    byte* data;
} Memory;

Memory* Memory_load(int size, const char* path);
int Memory_read(Memory* memory, int address, int memRead);
void Memory_write(Memory* memory, int address, int value, int memWrite);
void Memory_free(Memory* memory);

#endif
