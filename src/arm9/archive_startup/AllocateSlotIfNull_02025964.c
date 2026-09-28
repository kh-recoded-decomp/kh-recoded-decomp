#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    void **slots;
} ExtraTable;

typedef struct {
    u8 pad_00[0x1c8];
    ExtraTable *extra;
} Context;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, int size);

void AllocateSlotIfNull_02025964(Context *context, int index)
{
    if (context->extra->slots[index] == 0) {
        context->extra->slots[index] = NNSi_FndAllocFromDefaultHeap_0202a178(0xf2c);
        func_01ff8830(context->extra->slots[index], 0, 0xf2c);
    }
}
