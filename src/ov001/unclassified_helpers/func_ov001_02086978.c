#include "nitro/types.h"

extern void func_ov001_020645dc(u32 param1, u32 param2);
extern void func_ov001_020645e8(u32 param1, u32 param2);

void func_ov001_02086978(u32 param1, u32 param2, int useAlt) {
    if (useAlt != 0) {
        func_ov001_020645dc(param1, param2);
        return;
    }
    func_ov001_020645e8(param1, param2);
}
