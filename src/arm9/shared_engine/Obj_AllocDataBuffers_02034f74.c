#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *bufferA;
    void *bufferB;
    void *bufferC;
    s16 count;
    u8 pad_26[6];
    u8 flag2C;
} DataBuffers;

extern void *func_01ff86fc(u32 value, void *dest, u32 size);
extern void *func_0202a178(u32 size);

void Obj_AllocDataBuffers_02034f74(DataBuffers *obj, s32 count, s32 wantA, s32 wantB, s32 wantC)
{
    void *buf;

    if (wantA == 0) {
        buf = 0;
    } else {
        buf = func_0202a178(count << 2);
    }
    obj->bufferA = buf;

    if (wantB == 0) {
        buf = 0;
    } else {
        buf = func_0202a178(count << 2);
    }
    obj->bufferB = buf;

    if (wantC == 0) {
        buf = 0;
    } else {
        buf = func_0202a178(count << 2);
    }
    obj->bufferC = buf;

    func_01ff86fc(0, obj, 0x18);
    obj->count = (s16)count;
    obj->flag2C = 0;
}
