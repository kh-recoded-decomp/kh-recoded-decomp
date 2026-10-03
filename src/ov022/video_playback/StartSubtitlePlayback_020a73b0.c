#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b0];
    int state;
    u8 pad_8B4[4];
    int pendingFrame;
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7d80;

extern void ActivateSubtitleStream_020a88f0(void);

void StartSubtitlePlayback_020a73b0(void) {
    MoviePlayer *player = data_ov022_020b7d80;

    player->pendingFrame = -1;
    player->state = 2;
    ActivateSubtitleStream_020a88f0();
}
