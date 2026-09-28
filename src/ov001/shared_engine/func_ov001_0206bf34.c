#include "nitro/types.h"

extern int FreeBufferAndClearStatus_0206a918(int obj);
extern void func_020524e8(void *p);

void func_ov001_0206bf34(int manager)
{
    int i;

    i = 0;
    do {
        FreeBufferAndClearStatus_0206a918(manager + i * 0x30);
        i = i + 1;
    } while (i < 4);
    i = 0;
    do {
        FreeBufferAndClearStatus_0206a918(manager + 0xc0 + i * 0x30);
        i = i + 1;
    } while (i < 2);
    *(u32 *)(manager + 0x124) = 0;
    *(u32 *)(manager + 0x128) = 0;
    func_020524e8((void *)(manager + 300));
}
