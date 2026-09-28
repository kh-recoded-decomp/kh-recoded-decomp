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

int GetScrollTrackRow_020c13a8(int trackIndex)
{
    return g_menuScene_020c2520->scrollTracks[trackIndex].current >> 12;
}
