#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    s32 field_28;
} Manager;

typedef struct {
    s32 words[10];
    s32 last;
} Payload44;

extern void func_02040548(Manager **param1, void **args, s32 param3, u32 param4);

void func_02041064(Manager **param1, Payload44 **param2, s32 param3, u32 param4)
{
    Manager *manager = *param1;
    Payload44 payload = **param2;
    void *args[8];

    args[0] = &payload;
    payload.last = payload.last + manager->field_28;

    func_02040548(param1, args, param3, param4 | 2);
}
