#include "nitro/types.h"

extern int func_ov001_02087214(void);
extern u32 func_ov001_0208635c(int arg1, u32 arg2);

u32 func_ov001_02087224(u32 param1, u32 param2) {
    int obj = func_ov001_02087214();
    if (obj != 0) {
        return func_ov001_0208635c(obj, param2);
    }
    return 0;
}
