#include "nitro/types.h"

extern int data_ov001_0209f2c8;
extern void func_ov001_0209cae0(u16 id);

void CallIfSessionActive_02087e34(int id)
{
    if (data_ov001_0209f2c8 != -1) {
        func_ov001_0209cae0(id);
    }
}
