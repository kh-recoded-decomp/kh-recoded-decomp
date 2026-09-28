#include "nitro/types.h"

extern void func_ov010_020a0eec(void);
extern void func_ov001_020645e8(int eventId);

void func_ov010_020a0d00(u32 *actor)
{
    *actor = 0;
    func_ov010_020a0eec();
    func_ov001_020645e8(0x3713);
    func_ov001_020645e8(0x3716);
    func_ov001_020645e8(0x3717);
}
