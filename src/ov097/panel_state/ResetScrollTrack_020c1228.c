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

void ResetScrollTrack_020c1228(int trackIndex)
{
    ScrollTrack *tracks = g_menuScene_020c2520->scrollTracks;

    tracks[trackIndex].target = 0;
    tracks[trackIndex].current = 0;
}
