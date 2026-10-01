#include "nitro/types.h"

extern int data_ov001_0209f2c8;
extern void func_ov001_0209c650(u16 id, int arg);

void CallIfSessionActive_02087e98(int id, int arg)
{
    if (data_ov001_0209f2c8 != -1) {
        func_ov001_0209c650(id, arg);
    }
}
