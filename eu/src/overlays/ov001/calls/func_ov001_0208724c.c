#include "nitro/types.h"

extern int func_ov001_0208723c(void);
extern u32 func_ov001_02086384(int arg1, u32 arg2);

u32 func_ov001_0208724c(u32 param1, u32 param2) {
    int obj = func_ov001_0208723c();
    if (obj != 0) {
        return func_ov001_02086384(obj, param2);
    }
    return 0;
}
