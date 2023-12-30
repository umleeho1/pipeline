#include "cpu.h"



void IM_Init() {
	FILE* fp_in;
	uint32_t bin;
	uint32_t counter = 0x00000;

	fp_in = fopen("test_prog/input.bin", "rb");
	if (fp_in == NULL) {
		printf("Error: program not found.");
		exit(0);
	}


	memset(&InstMemory, 0, sizeof(InstMemory));
	while (fread(&bin, 1, sizeof(int), fp_in) == 4) {

		for (int i = 3; i >= 0; i--) {
			InstMemory[counter + i] = bin & 0xff;

			bin = bin >> 8;
		}
	
		counter += 4;
	}

	fclose(fp_in);
}


/* fetch the instruction from the instruction memory */
uint32_t IM_ReadMemory(uint32_t ReadAddress) {
	return
		(InstMemory[ReadAddress + 3] << 24) |
		(InstMemory[ReadAddress + 2] << 16) |
		(InstMemory[ReadAddress + 1] << 8) |
		(InstMemory[ReadAddress + 0] << 0);
}