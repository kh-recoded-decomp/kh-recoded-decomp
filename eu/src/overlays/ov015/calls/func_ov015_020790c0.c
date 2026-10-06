#include "nitro/types.h"

extern int func_ov015_020790e8(void);
extern int IsCursorOffscreen(void);

BOOL func_ov015_020790c0(void) {
    if ((func_ov015_020790e8() != 0) && (IsCursorOffscreen() != 0)) {
        return 1;
    }
    return 0;
}
