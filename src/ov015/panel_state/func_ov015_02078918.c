#include "nitro/types.h"

extern int IsGlobalBit0Set_020632ac(void);
extern int func_ov002_020632c8(void);
extern int func_ov015_020790c0(void);

BOOL func_ov015_02078918(void) {
    BOOL result;

    result = 0;
    if ((IsGlobalBit0Set_020632ac() != 0) || (func_ov002_020632c8() != 0) ||
        (func_ov015_020790c0() != 0)) {
        result = 1;
    }
    return result;
}
