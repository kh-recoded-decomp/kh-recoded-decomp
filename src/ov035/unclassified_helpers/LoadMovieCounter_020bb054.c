#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2a];
    s16 counter;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern int ReadSessionPackedBits_02064574(int bitOffset, int bitCount);
extern int GetMovieCounterLimit_020bafc4(int which);
extern void StoreMovieCounter_020bb014(int which, int value);

int LoadMovieCounter_020bb054(int which)
{
    int value;

    if (which == 0) {
        value = g_movieContext_020bc4e0->counter;
    } else {
        value = ReadSessionPackedBits_02064574(which == 1 ? 0x3703 : 0x3713, 0x10);
    }
    if (GetMovieCounterLimit_020bafc4(which) < value) {
        value = GetMovieCounterLimit_020bafc4(which);
        StoreMovieCounter_020bb014(which, value);
    }
    return value;
}