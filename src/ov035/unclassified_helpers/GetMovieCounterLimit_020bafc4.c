#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2c];
    s16 baseLimit;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;

int GetMovieCounterLimit_020bafc4(int which)
{
    switch (which) {
    case 0:
        return g_movieContext_020bc4e0->baseLimit;
    case 1:
        return (g_movieContext_020bc4e0->baseLimit * 130 + 50) / 100;
    case 2:
        return (g_movieContext_020bc4e0->baseLimit * 115 + 50) / 100;
    }
    return -1;
}