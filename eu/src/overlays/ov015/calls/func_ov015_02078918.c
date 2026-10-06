#include "nitro/types.h"

extern int func_ov002_020632ac(void);
extern int IsButtonBPressed(void);
extern int func_ov015_020790c0(void);

BOOL func_ov015_02078918(void) {
    BOOL result;

    result = 0;
    if ((func_ov002_020632ac() != 0) || (IsButtonBPressed() != 0) ||
        (func_ov015_020790c0() != 0)) {
        result = 1;
    }
    return result;
}
