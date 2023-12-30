#include "../header/cpu/ALUnit.h"
#include <stdio.h>
#include <stdlib.h>

AluOperation operations[] = {
    {ADDITION, NULL},
    {SUBTRACTION, NULL},
    {OR, NULL},
    {SHIFT_LEFT, NULL},
    {SET_LESS_THAN, NULL},
    {NONE, NULL},
    {EQUAL, NULL},
    {NOT_EQUAL, NULL}
};

void initializeOperations() {
    operations[ADDITION].operation = addOperation;
    operations[SUBTRACTION].operation = subtractOperation;
    operations[OR].operation = orOperation;
    operations[SHIFT_LEFT].operation = shiftLeftOperation;
    operations[SET_LESS_THAN].operation = setLessThanOperation;
    operations[NONE].operation = noneOperation;
    operations[EQUAL].operation = equalOperation;
    operations[NOT_EQUAL].operation = notEqualOperation;
}

int addOperation(int src1, int src2) {
    return src1 + src2;
}

int subtractOperation(int src1, int src2) {
    return src1 - src2;
}

int orOperation(int src1, int src2) {
    return src1 | src2;
}

int shiftLeftOperation(int src1, int src2) {
    return src1 << src2;
}

int setLessThanOperation(int src1, int src2) {
    return (src1 < src2) ? 1 : 0;
}

int noneOperation(int src1, int src2) {
    return 0;
}

int equalOperation(int src1, int src2) {
    return (src1 == src2) ? 1 : 0;
}

int notEqualOperation(int src1, int src2) {
    return (src1 != src2) ? 1 : 0;
}

AluResult operate(AluOp aluOp, int src1, int src2) {
    for (int i = 0; i < sizeof(operations) / sizeof(AluOperation); i++) {
        if (operations[i].aluOp == aluOp) {
            AluResult result;
            result.value = operations[i].operation(src1, src2);
            result.isTrue = (result.value != 0);
            return result;
        }
    }
    fprintf(stderr, "Opcodes that cannot be computed: %d\n", aluOp);
    exit(1);
}
