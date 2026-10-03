#include "nitro/types.h"

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern void func_0204f204(void *pool, s32 recordIndex, u16 cell);
extern void func_0204f378(void *pool, s32 recordIndex, BOOL visible);

void DrawOv038PercentDigits_020bb35c(s32 poolIndex, s32 firstRecord, s32 value)
{
    BOOL visible = FALSE;
    Ov038Context *ctx = g_ov038Context_020bd144;
    s32 divisor = 100;
    s32 index;
    u16 digit;

    for (index = 0; index < 4; index++) {
        if (index == 3) {
            digit = 10;
        } else {
            digit = value / divisor;
        }
        if (digit != 0 || index == 2) {
            visible = TRUE;
        }
        value = value % divisor;
        divisor = divisor / 10;
        func_0204f204(&ctx->pools[poolIndex], firstRecord + index, digit);
        func_0204f378(&ctx->pools[poolIndex], firstRecord + index, visible);
    }
}
