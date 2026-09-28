#include "nitro/types.h"

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

typedef struct StrmPlayer {
    u8 pad_00[0xf0];
    NNSSndFader fader;
    u8 pad_100[0x118 - 0x100];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL unk_bit2 : 1;
    BOOL stopFlag : 1;
    u8 pad_11c[0x158 - 0x11c];
    int fadeCounter;
} StrmPlayer;

extern void ForceStopStrmPlayer_02020810(StrmPlayer *player);
extern void func_020218d4(NNSSndFader *fader, int target, int frame);

void StopStrmPlayerWithFade_020207b8(StrmPlayer *player, int fadeFrames) {
    if (!player->playFlag) {
        ForceStopStrmPlayer_02020810(player);
        return;
    }
    if (fadeFrames == 0) {
        ForceStopStrmPlayer_02020810(player);
        return;
    }
    func_020218d4(&player->fader, 0, fadeFrames);
    player->fadeCounter = 0;
    player->stopFlag = TRUE;
}
