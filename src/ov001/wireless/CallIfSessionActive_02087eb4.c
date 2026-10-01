#include "nitro/types.h"

extern int data_ov001_0209f2c8;
extern void func_ov001_0209c6c8(u16 id, int arg, int extra);

void CallIfSessionActive_02087eb4(int id, int arg, int extra)
{
    if (data_ov001_0209f2c8 != -1) {
        func_ov001_0209c6c8(id, arg, extra);
    }
}
