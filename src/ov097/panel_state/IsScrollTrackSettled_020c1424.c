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

BOOL IsScrollTrackSettled_020c1424(int trackIndex)
{
    ScrollTrack *tracks = g_menuScene_020c2520->scrollTracks;
    ScrollTrack *entry = &tracks[trackIndex];
    fx32 distance = entry->target - entry->current;

    if (distance < 0) {
        distance = (fx32)(((s64)distance * -1 + 0x800) >> 12);
    }
    return (distance >> 12) < 1;
}
