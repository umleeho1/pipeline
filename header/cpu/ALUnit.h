#ifndef ALUNIT_H
#define ALUNIT_H

typedef enum {
    ADDITION,
    SUBTRACTION,
    OR,
    SHIFT_LEFT,
    SET_LESS_THAN,
    NONE,
    EQUAL,
    NOT_EQUAL
} AluOp;

typedef struct {
    int value;
    int isTrue;
} AluResult;

typedef struct {
    AluOp aluOp;
    int src1;
    int src2;
} AluOperands;

typedef struct {
    AluOp aluOp;
    int (*operation)(int, int);
} AluOperation;

AluResult operate(ALUnit* alUnit, AluOperands operands);
void destroyALUnit(ALUnit* alUnit);

#endif
