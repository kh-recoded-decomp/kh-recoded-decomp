#include "nitro/types.h"

extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void func_02052570(void *o);

void func_ov001_0206bfec(int manager, int id)
{
    if (*(int *)(manager + 0x128) == id) {
        *(int *)(manager + 0x120) = manager + 0xc0;
        return;
    }
    *(int *)(manager + 0x128) = id;
    *(u32 *)(manager + 0x124) = 1;
    *(int *)(manager + 0x120) = manager + 0xc0;
    func_02052528((void *)(manager + 300), 2, 0x2d000, 0, 400);
    func_02052570((void *)(manager + 300));
}
