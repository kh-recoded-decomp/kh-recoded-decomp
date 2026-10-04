#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 target;
    fx32 current;
} ScrollTrack;

typedef struct {
    u8 pad_0000[0xf084];
    ScrollTrack scrollTracks[2];
} MenuScene;

extern MenuScene *g_menuScene_020c2520;
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

void EaseScrollTrack_020c13c8(int trackIndex)
{
    ScrollTrack *tracks = g_menuScene_020c2520->scrollTracks;
    ScrollTrack *entry = &tracks[trackIndex];

    entry->current += (fx32)(((s64)(tracks[trackIndex].target - entry->current) * FX_Div_01ff9c84(0x7b, 0x266) +
                               0x800) >> 12);
}
