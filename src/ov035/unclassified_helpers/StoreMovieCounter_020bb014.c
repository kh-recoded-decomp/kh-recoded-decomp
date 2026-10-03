#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2a];
    s16 counter;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern int func_ov035_020bafc4(int which);
extern void WriteSessionPackedBits_0206459c(int bitIndex, int bitCount, int value);

void StoreMovieCounter_020bb014(int which, int value)
{
    if (func_ov035_020bafc4(which) < value) {
        value = func_ov035_020bafc4(which);
    }
    if (which == 0) {
        g_movieContext_020bc4e0->counter = value;
    } else {
        WriteSessionPackedBits_0206459c(which == 1 ? 0x3703 : 0x3713, 0x10, value);
    }
}