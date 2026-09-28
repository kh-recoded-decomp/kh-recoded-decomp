#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void *listHeadPtr;
    u8 pad_14[0x1c];
    u32 param2Field;
    s32 param3Field;
} Obj;

extern u32 CheckTypeAndComputeSpan_0200d05c(Obj *obj, u32 outAddr);
extern u32 CheckTypeAndComputeSpan_0200d01c(Obj *obj, u32 outAddr);
extern void func_0200a930(Obj *obj, int a, int b);

int func_0200b6c8(Obj *obj, u32 param2, int param3)
{
    u32 spanEnd;
    int spanStart;

    if (CheckTypeAndComputeSpan_0200d05c(obj, (u32)&spanStart) != 0 &&
        CheckTypeAndComputeSpan_0200d01c(obj, (u32)&spanEnd) != 0) {
        if ((u32)(spanStart + param3) > spanEnd) {
            param3 = spanEnd - spanStart;
        }
    }

    void *slot = &obj->param2Field;
    obj->listHeadPtr = slot;
    obj->param2Field = param2;
    *((s32 *)slot + 1) = param3;
    func_0200a930(obj, 0, 0);
    return param3;
}
