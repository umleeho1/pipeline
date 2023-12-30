#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "register.h"
#include "instruction.h"

#define LINE    printf("---------------------------------------------------------------\n")


/* size variables */
char PREDICTOR;  // branch predictor 
char* PROGRAM; //  executing program
#define REGSIZE 32 // size of the registers
#define BHTENTRY 0x100 // size of the branch history table
#define PHTENTRY 0x100 // size of the pattern history table
#define LHTENTRY 0x100 // size of the local history register table
#define MEMSIZE 0x1000000 // size of the memory -> 16MB


/* instruction type */
enum inst_type { J_type, I_type, R_type };


/* instruction fields */
typedef struct instruction {
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t funct;
    uint16_t immediate;
    uint32_t address;
} instruction;


/* control signals for each stages */
/* ID stage signals */
bool Jump;                // jump
bool SignEx;             // sign extended
uint8_t FwdA;          // forward A
uint8_t FwdB;          // forward B
bool PCWrite;          // PC write
bool IFIDWrite;        // IFID latch write
bool IDEXCtrlSrc;     // IDEX initialization

/* EX stage signals */
typedef struct IDEX_SIG {
    bool RegDst;            // register destination
    bool ReAddr;           // return address of 31
    bool RegWrite;       // register write
    bool ALUSrc;            // ALU source
    bool Shift;                // bit shift
    bool Rtype;             // R type instruction
    uint8_t ALUOp;      // ALU operation
    bool Equal;              // branch equal
    bool MemRead;     // memory read
    bool MemWrite;    // memory write
    bool Branch;           // branch taken
    bool MemToReg;   // memory to register
    bool JumpReg;       // jump register 
    bool JumpLink;      // jump link
    bool PreTaken;       // predict taken
  
} IDEX_SIG;

/* MEM stage signals */
typedef struct EXMEM_SIG {
    bool RegWrite;       // register write
    bool ALUSrc;            // ALU source
    bool Shift;                // bit shift
    bool Rtype;             // R type instruction
    uint8_t ALUOp;      // ALU operation
    bool Equal;              // branch equal
    bool MemRead;     // memory read
    bool MemWrite;    // memory write
    bool Jump;              // jump
    bool Branch;           // branch taken
    bool MemToReg;   // memory to register
    bool JumpReg;       // jump register 
    bool JumpLink;      // jump link
} EXMEM_SIG;

/* WB stage signals */
typedef struct MEMWB_SIG {
    bool RegWrite;       // register write
    bool MemToReg;   // memory to register
    bool JumpLink;      // jump link
} MEMWB_SIG;


/* latches for each stages */
/* IFID latch */
typedef struct IFID_LAT {
    bool valid;                // latch valid bit
    uint32_t NPC;          // PC + 4
    uint32_t IR;              // instruction register
    uint32_t BHTIdx;     // branch history index
    uint32_t PHTIdx;     // patternt history index
    uint32_t LHTIdx;     // patternt history index
    bool PreTaken;        // predict taken

} IFID_LAT;

/* IDEX latch */
typedef struct IDEX_LAT {
    bool valid;                    // latch valid bit
    uint32_t NPC;             // PC + 4
    uint32_t ReadData1; // read data from R[rs]
    uint32_t ReadData2; // read data from R[rt]
    uint8_t rt;                    // target register
    uint8_t rd;                   // destination register
    uint8_t rs;                    // source register
    uint32_t imm;             // immediate
    uint8_t funct;              // function field
    uint8_t shamt;            // shift amount
    uint8_t opcode;          // oepration code
    IDEX_SIG Control;      // control signals for later stages
} IDEX_LAT;

/* EXMEM latch */
typedef struct EXMEM_LAT {
    bool valid;                     // latch valid bit
    uint32_t NPC;               // PC + 4
    uint32_t BrTarget;       // branch target address 
    bool bcond;                  // branch condition bit
    uint32_t ALUResult;    // arithmetic logic unit operation result
    uint32_t ReadData1;  // read data from R[rs]
    uint32_t ReadData2;  // read data from R[rt]
    uint8_t rd;                    // destination register 
    EXMEM_SIG Control; // control signals for later stages
} EXMEM_LAT;

/* MEMWB latch */
typedef struct MEMWB_LAT {
    bool valid;                      // latch valid bit
    uint32_t NPC;                // PC + 4
    uint32_t ReadData;      // read data from M[R[rs] + sign_ext_imm]
    uint32_t ALUResult;     // arithmetic logic unit operation result
    uint8_t rd;                      // destination register 
    MEMWB_SIG Control; // control signals for write back stage
} MEMWB_LAT;




/* addr */
uint32_t PCAddr(uint32_t PC);
uint32_t SignExtend(uint16_t immediate);
uint32_t ZeroExtend(uint16_t immediate);
uint32_t JumpAddr(uint32_t PC, uint32_t address);
uint32_t BranchAddr(uint32_t PC, uint32_t immediate);


/* multiplexer */
uint32_t MUX2(uint32_t IN1, uint32_t IN2, bool S);
uint32_t MUX3(uint32_t IN1, uint32_t IN2, uint32_t IN3, uint8_t S);


/* control unit */
void CU_Init();
void CU_Operation(uint8_t opcode, uint32_t funct);


/* instruction memory */
void IM_Init();
uint32_t IM_ReadMemory(uint32_t ReadAddress);


/* register file */
void RF_Init();
void RF_Read(uint8_t RdReg1, uint8_t RdReg2);
void RF_Write(uint8_t WrtReg, uint32_t WrtData, bool WrtEnable);


/* arithmetic logic unit */
uint8_t ALU_Control(uint8_t ALUOp, uint8_t opcode);
uint32_t ALU_Operation(uint8_t ALU_Control, uint32_t operand1, uint32_t operand2);


/* data memory */
void DM_Init();
void DM_MemoryAccess(uint32_t Address, int size, uint32_t WriteData, bool MemRead, bool MemWrite);


/* latch */
void LAT_Init();
void LAT_Update();
void IDEX_LAT_WIRE();
void IDEX_EXMEM_CPY();
void EXMEM_LAT_WIRE();
void EXMEM_MEMWB_CPY();
void MEMWB_LAT_WIRE();


/* forward unit */
void FW_Init();
void FW_Operation();


/* hazard detection unit */
void HU_Init();
void HU_Operation();

/* log */
void LOG_Init();
void LOG_Print();

/* log variables */
int cycle;
int total_instruction;
int memory_access;
int register_operation;
int branch_taken;
int jump_instruction;


/* control process unit */
/* control process unit operations */
void IF();
void ID();
void EX();
void MEM();
void WB();
void init();
void terminate();

/* control process unit variables */
uint32_t PC; // program counter
instruction* inst; // instruction structure
uint32_t Register[REGSIZE]; // register file
uint8_t DataMemory[MEMSIZE]; // data memory
uint8_t InstMemory[MEMSIZE]; // instruction memory

IFID_LAT IFID[2]; // IFID IN/OUT latch
IDEX_LAT IDEX[2]; // IDEX IN/OUT latch
EXMEM_LAT EXMEM[2]; // EXMEM IN/OUT latch
MEMWB_LAT MEMWB[2]; // MEMWB IN/OUT latch


