#include "nitro/types.h"

extern u32 g_overlayWorkData_020d2c20;
extern u32 func_ov052_020ccc60();
extern u32 func_ov001_02063a38();
extern void FreeCueTable_020bdfec();
extern u32 func_ov001_0206e31c();
extern u32 func_ov010_020a1808();

void ShutdownOverlay053_020d2628(void)
{
    s32 result;

    if (g_overlayWorkData_020d2c20 != 0) {
        func_ov052_020ccc60();
        result = func_ov001_02063a38();
        if (result == 6) {
            FreeCueTable_020bdfec();
        }
        result = func_ov001_0206e31c();
        if (result != 0) {
            func_ov010_020a1808();
        }
        g_overlayWorkData_020d2c20 = 0;
    }
}
