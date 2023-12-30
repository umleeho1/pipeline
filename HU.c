#include "cpu.h"


/* initialize hazard detection unit signals */
void HU_Init() {
	PCWrite = true;
	IFIDWrite = true;
	IDEXCtrlSrc = false;
}


/* hazard detection unit operation*/
void HU_Operation() {
	if (IDEX[0].Control.MemRead && (IDEX[0].rd == inst->rs || IDEX[0].rd == inst->rt)) {
		PCWrite = false;
		IFIDWrite = false;
		IDEXCtrlSrc = true;
	}
	else {
		PCWrite = true;
		IFIDWrite = true;
		IDEXCtrlSrc = false;
	}
}