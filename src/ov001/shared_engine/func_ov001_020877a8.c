#include "nitro/types.h"

extern u32 func_ov001_0209c3c0(void);
extern int data_0209f2c8;

u32 func_ov001_020877a8(void) {
    if (data_0209f2c8 != -1) {
        return func_ov001_0209c3c0();
    }
    return 0;
}
