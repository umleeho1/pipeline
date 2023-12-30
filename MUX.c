#include "cpu.h"


/* multiplexer for 2 inputs(MUX2) */
uint32_t MUX2(uint32_t IN1, uint32_t IN2, bool S) {
	return S ? IN2 : IN1;
}


/* multiplexer for 3 inputs(MUX3) */
uint32_t MUX3(uint32_t IN1, uint32_t IN2, uint32_t IN3, uint8_t S) {
	if (S == 0b00) return IN1;
	if (S == 0b01) return IN2;
	if (S == 0b10) return IN3;
}