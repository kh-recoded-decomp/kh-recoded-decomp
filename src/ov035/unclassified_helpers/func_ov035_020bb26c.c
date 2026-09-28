#include "nitro/types.h"

extern void func_ov001_0206459c(u32 id, int size, int value);
extern void func_ov001_020645e8(u32 id);

void func_ov035_020bb26c(void) {
    func_ov001_020645e8(0x3702);
    func_ov001_020645e8(0x379b);
    func_ov001_0206459c(0x3791, 10, 0);
    func_ov001_020645e8(0x3723);
    func_ov001_020645e8(0x3724);
}
