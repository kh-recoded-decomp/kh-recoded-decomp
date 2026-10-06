#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);
extern s32 CountAssignedFieldSlots(void);
extern void FreePointerIfSet(u32 context);

void func_ov001_0206fa2c(u32 context)
{
    s32 count;
    s32 index;

    FreePointerIfSet(context + 0x2d8);
    FreePointerIfSet(context + 0x2cc);
    DestroyFndObjectList(context + 0x1fc);
    count = CountAssignedFieldSlots();
    index = 0;
    if (0 < count + 1) {
        do {
            DestroyFndObjectList(context + 0x230 + index * 0x34);
            index = index + 1;
        } while (index < count + 1);
    }
}
