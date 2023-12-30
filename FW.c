#include "cpu.h"


/* initialize forward unit signal */
void FW_Init() {
	FwdA = 0b00;
	FwdB = 0b00;
}


/* forward unit operation for data dependency control */
void FW_Operation() {
	FwdA = 0b00;
	FwdB = 0b00;

	// EXMEM forwarding
	if (EXMEM[0].rd != 0 && EXMEM[0].Control.RegWrite) {
		if (EXMEM[0].rd == IDEX[0].rs) {
			FwdA = 0b10;
		}
		if (EXMEM[0].rd == IDEX[0].rt) {
			FwdB = 0b10;
		}
	}

	// MEMWB forwarding
	if (MEMWB[0].rd != 0 && MEMWB[0].Control.RegWrite) {
		if (EXMEM[0].rd != IDEX[0].rs && MEMWB[0].rd == IDEX[0].rs) {
			FwdA = 0b01;
		}
		if (EXMEM[0].rd != IDEX[0].rt && MEMWB[0].rd == IDEX[0].rt) {
			FwdB = 0b01;
		}
	}
}