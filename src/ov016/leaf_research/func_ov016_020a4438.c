#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x47];
    s8 mode;
} ObjectState;

typedef struct {
    u32 pad_000;
    s32 offset;
} OutputRecord;

void func_ov016_020a4438(ObjectState *obj, OutputRecord *out)
{
    if (obj->mode == 1) {
        out->offset += 0x2d;
    }
}
