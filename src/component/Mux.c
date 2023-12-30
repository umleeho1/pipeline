#include "../header/component/Mux.h"


int mux(int signal, int trueResult, int falseResult) {
    return signal ? trueResult : falseResult;
}
