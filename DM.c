#include "cpu.h"


/* initialize data memory*/
void DM_Init() {
	memset(&DataMemory, 0, sizeof(DataMemory));
}


/* data memory access */
void DM_MemoryAccess(uint32_t Address, int size, uint32_t WriteData, bool MemRead, bool MemWrite) {
	/* memory read operaiton*/
	if ((MemRead == true) && (MemWrite == false)) {
		memory_access++;
		uint32_t result = 0;
		for (int i = 0; i < (size / 8); i++) {
			result = result << 8;
			result = result | DataMemory[Address + i];
		}
		MEMWB[0].ReadData = result;
	}

	/* memory write operaitons */
	if ((MemRead == false) && (MemWrite == true)) {
		memory_access++;
		for (int i = (size / 8) - 1; i >= 0; i--) {
			DataMemory[Address + i] = WriteData & 0xff;
			WriteData = WriteData >> 8;
		}
	}
}