#include "cpu.h"

/* initialize log variables */
void LOG_Init() {
	cycle = 0;
	total_instruction = 0;	 
	memory_access = 0;
	register_operation = 0;
	branch_taken = 0;
	jump_instruction = 0;
}


/* show the micro-architectural state from the previous stages */
void LOG_Print() {
	/* cyclee */
	printf("Cycle: %d\n", cycle);

	/* IF (instruction fetch) stage */
	if (PC != 0xffffffff) printf("[IF] :: PC: %08x, IR: %08x\n", IFID[0].NPC - 4, IFID[0].IR);
	else printf("[IF] :: Program Terminated\n");

	/* ID (instruction decode) stage */
	if (IFID[1].valid) {
		enum inst_type type;
		switch (inst->opcode)
		{
		case 0x00:	type = R_type; break;
		case 0x02:
		case 0x03:	type = J_type; break;
		default:		type = I_type; break;
		}

		switch (type)
		{
		case J_type:
			printf("[ID] :: opcode: (%02x) address: %07x\n", inst->opcode, inst->address);
			break;
		case I_type:
			if (inst->opcode == J) printf("[ID] :: Jump to %08x\n", IDEX[1].NPC - 4);
			else if (inst->opcode == JAL) printf("[ID] :: Jump to: %08x\n", IDEX[1].NPC - 4);
			else printf("[ID] :: opcode: (%02x) rs: %d rt: %d immediate: %04x\n", inst->opcode, inst->rs, inst->rt, inst->immediate);
			break;
		case R_type:
			if (inst->opcode == JR) printf("[ID] :: Jump to: %08x = R[%d]\n", IDEX[1].NPC - 4, IDEX[1].rs);
			else if (inst->opcode == JALR) printf("[ID] :: Jump to: %08x\n", IDEX[1].NPC - 4);
			else printf("[ID] :: opcode: (%02x) rs: %d rt: %d rd: %d shamt: %02x funct: (%02x)\n", inst->opcode, inst->rs, inst->rt, inst->rd, inst->shamt, inst->funct);
			break;
		}
	}
	else printf("[ID] :: Stall\n");

	/* EX (execution) stage */
	if (IDEX[1].valid) {
		switch (IDEX[1].opcode)
		{
		// I type
		case ADDI:
		case ADDIU: printf("[EX] :: R[%d]: %08x = R[%d] + %08x\n", IDEX[1].rt, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;
		case ANDI:	printf("[EX] :: R[%d]: %08x = R[%d] & %08x\n", IDEX[1].rt, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;
		case BEQ:
			if (MUX2(EXMEM[0].bcond && EXMEM[0].Control.Branch, !EXMEM[0].bcond && EXMEM[0].Control.Branch, EXMEM[0].Control.Equal))
				printf("[EX] :: Jump to  %08x = R[%d] == R[%d]\n", IDEX[1].NPC - 4, IDEX[1].rs, IDEX[1].rt);
			else
				printf("[EX] :: Branch equal X = R[%d] != R[%d]\n", IDEX[1].rs, IDEX[1].rt);
			break;
		case BNE:
			if (MUX2(EXMEM[0].bcond && EXMEM[0].Control.Branch, !EXMEM[0].bcond && EXMEM[0].Control.Branch, EXMEM[0].Control.Equal))
				printf("[EX] :: Branch not equal X = R[%d] == R[%d]\n", IDEX[1].rs, IDEX[1].rt);
			else
				printf("[EX] :: Jump to  %08x = R[%d] != R[%d]\n", IDEX[1].NPC - 4, IDEX[1].rs, IDEX[1].rt);
			break;
		case LUI:	printf("[EX] :: R[%d]: %08x = R[%d] << 16\n", IDEX[1].rt, EXMEM[0].ALUResult, IDEX[1].imm); break;
		case LW:	printf("[EX] :: Load Memory Address: %08x = R[%d] + %08x\n", EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;
		case ORI:	printf("[EX] :: R[%d]: %08x = R[%d] | %08x\n", IDEX[1].rt, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;
		case SLTI:
		case SLTIU:	printf("[EX] :: R[%d]: %d = (R[%d] < %08x)? 1 : 0\n", IDEX[1].rt, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;
		case SW: printf("[EX] :: Store Memory Address: %08x = R[%d] + %08x\n", EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].imm); break;

		// J type
		case J: printf("[EX] :: Jump to %08x\n", IDEX[1].NPC - 4); break;
		case JAL:  printf("[EX] :: R[31]: %08x; PC: %08x\n", IDEX[1].NPC, IDEX[1].NPC - 4); break;

		// R type
		case 0x00:
			switch (IDEX[1].funct)
			{
			case ADD:
			case ADDU:  printf("[EX] :: R[%d]: %08x = R[%d] + R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case AND:   printf("[EX] :: R[%d]: %08x = R[%d] & R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;	
			case JR:    printf("[EX] :: PC: %08x = R[%d]\n", IDEX[1].NPC - 4, IDEX[1].rs); break;
			case JALR:  printf("[EX] :: R[31]: %08x; PC: %08x\n", IDEX[1].NPC, IDEX[1].NPC - 4); break;
			case NOR:   printf("[EX] :: R[%d]: %08x = ~(R[%d] | R[%d])\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case OR:    printf("[EX] :: R[%d]: %08x = R[%d] | R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case SLT:
			case SLTU:  printf("[EX] :: R[%d]: %d = (R[%d] + R[%d]) ? 1 : 0\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case SLL:   printf("[EX] :: R[%d]: %08x = R[%d] << R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case SRL:   printf("[EX] :: R[%d]: %08x = R[%d] >> R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			case SUB:
			case SUBU:  printf("[EX] :: R[%d]: %08x = R[%d] - R[%d]\n", IDEX[1].rd, EXMEM[0].ALUResult, IDEX[1].rs, IDEX[1].rt); break;
			} 
			break;

		default: printf("[EX] :: No Execution\n");
		}
	}
	else printf("[EX] :: Stall\n");

	/* MEM (memory access) stage */
	if (EXMEM[1].valid) {
		if (EXMEM[1].Control.MemRead && !EXMEM[1].Control.MemWrite) printf("[MA] :: ReadData: %08x = M[R[%08x]\n", MEMWB[0].ReadData, EXMEM[1].ALUResult);
		else if (EXMEM[1].Control.MemRead && !EXMEM[1].Control.MemWrite) printf("[MA] :: M[%08x]: %08x\n", EXMEM[1].ALUResult, EXMEM[1].ReadData2);
		else printf("[MA] :: No Memory Access\n");
	}
	else printf("[MA] :: Stall \n");

	/* WB (write back) stage */
	if (MEMWB[1].valid) {
		if (MEMWB[1].Control.RegWrite) printf("[WB] :: R[%d]: %08x\n", MEMWB[1].rd, MUX2(MUX2(MEMWB[1].ALUResult, MEMWB[1].ReadData, MEMWB[1].Control.MemToReg), MEMWB[1].NPC, MEMWB[1].Control.JumpLink));
		else printf("[WB] :: No Register Write Back\n");
	}
	else printf("[WB] :: Stall\n");
}