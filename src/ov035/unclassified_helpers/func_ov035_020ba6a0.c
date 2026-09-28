#include "nitro/types.h"

extern void func_ov035_020bad64(void);
extern int func_ov041_020bcb28(void);

u32 func_ov035_020ba6a0(void) {
    if (func_ov041_020bcb28() != 0) {
        func_ov035_020bad64();
        return 7;
    }
    return 0xffffffff;
}
