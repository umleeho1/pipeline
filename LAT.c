#include "cpu.h"


/* initialize latches of each stage*/
void LAT_Init() {
	IFID[0].valid = false;
	IDEX[0].valid = false;
	EXMEM[0].valid = false;
	MEMWB[0].valid = false;

	memset(&IFID[0], 0, sizeof(IFID_LAT));
	memset(&IFID[1], 0, sizeof(IFID_LAT));
	memset(&IDEX[0], 0, sizeof(IDEX_LAT));
	memset(&IDEX[1], 0, sizeof(IDEX_LAT));
	memset(&EXMEM[0], 0, sizeof(EXMEM_LAT));
	memset(&EXMEM[1], 0, sizeof(EXMEM_LAT));
	memset(&MEMWB[0], 0, sizeof(MEMWB_LAT));
	memset(&MEMWB[1], 0, sizeof(MEMWB_LAT));
}


/* update latches */
void LAT_Update() {
	memcpy(&IFID[1], &IFID[0], sizeof(IFID_LAT));
	memcpy(&IDEX[1], &IDEX[0], sizeof(IDEX_LAT));
	memcpy(&EXMEM[1], &EXMEM[0], sizeof(EXMEM_LAT));
	memcpy(&MEMWB[1], &MEMWB[0], sizeof(MEMWB_LAT));

	memset(&IFID[0], 0, sizeof(IFID_LAT));
	memset(&IDEX[0], 0, sizeof(IDEX_LAT));
	memset(&EXMEM[0], 0, sizeof(EXMEM_LAT));
	memset(&MEMWB[0], 0, sizeof(MEMWB_LAT));
}


/* wire the values into IDEX latch*/
void IDEX_LAT_WIRE() {
	IDEX[0].rs = inst->rs;
	IDEX[0].rt = inst->rt;
	IDEX[0].rd = inst->rd;
	IDEX[0].NPC = IFID[1].NPC;
	IDEX[0].funct = inst->funct;
	IDEX[0].shamt = inst->shamt;
	IDEX[0].opcode = inst->opcode;
	IDEX[0].Control.PreTaken = IFID[1].PreTaken;
	IDEX[0].imm = MUX2(ZeroExtend(inst->immediate), SignExtend(inst->immediate), SignEx);
}


/* copy the signals and values from IDEX latch to EXMEM latch */
void IDEX_EXMEM_CPY() {
	EXMEM[0].Control.ALUOp = IDEX[1].Control.ALUOp;
	EXMEM[0].Control.ALUSrc = IDEX[1].Control.ALUSrc;
	EXMEM[0].Control.Branch = IDEX[1].Control.Branch;
	EXMEM[0].Control.Equal = IDEX[1].Control.Equal;
	EXMEM[0].Control.JumpLink = IDEX[1].Control.JumpLink;
	EXMEM[0].Control.JumpReg = IDEX[1].Control.JumpReg;
	EXMEM[0].Control.MemRead = IDEX[1].Control.MemRead;
	EXMEM[0].Control.MemToReg = IDEX[1].Control.MemToReg;
	EXMEM[0].Control.MemWrite = IDEX[1].Control.MemWrite;
	EXMEM[0].Control.RegWrite = IDEX[1].Control.RegWrite;
	EXMEM[0].Control.Rtype = IDEX[1].Control.Rtype;
	EXMEM[0].Control.Shift = IDEX[1].Control.Shift;
}


/* wire the values into EXMEM latch*/
void EXMEM_LAT_WIRE() {
	EXMEM[0].NPC = IDEX[1].NPC;
	EXMEM[0].bcond = EXMEM[0].ALUResult;
	EXMEM[0].BrTarget = BranchAddr(IDEX[1].NPC, IDEX[1].imm);
	EXMEM[0].rd = MUX2(MUX2(IDEX[1].rt, IDEX[1].rd, IDEX[1].Control.RegDst), ra, IDEX[1].Control.ReAddr);
}


/* copy the signals and values from EXMEM latch to MEMWB latch*/
void EXMEM_MEMWB_CPY() {
	MEMWB[0].Control.MemToReg = EXMEM[1].Control.MemToReg;
	MEMWB[0].Control.RegWrite = EXMEM[1].Control.RegWrite;
	MEMWB[0].Control.JumpLink = EXMEM[1].Control.JumpLink;
}


/* wire the values into MEMWB latch */
void MEMWB_LAT_WIRE() {
	MEMWB[0].rd = EXMEM[1].rd;
	MEMWB[0].NPC = EXMEM[1].NPC;
	MEMWB[0].ALUResult = EXMEM[1].ALUResult;
}