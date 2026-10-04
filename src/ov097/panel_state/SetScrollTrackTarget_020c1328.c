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

void SetScrollTrackTarget_020c1328(int trackIndex, int row)
{
    ScrollTrack *tracks = g_menuScene_020c2520->scrollTracks;

    tracks[trackIndex].target = (fx32)((float)row > 0 ? 0.5f + 4096.0f * (float)row : 4096.0f * (float)row - 0.5f);
}
