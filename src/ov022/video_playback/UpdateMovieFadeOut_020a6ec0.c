#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b8];
    int fadeLevel;
} MoviePlayer;

extern int GetSubtitleStreamFrame_020a8918(void);
extern void func_02006748(vu16 *brightnessReg, int brightness);

void UpdateMovieFadeOut_020a6ec0(MoviePlayer *player) {
    if (player->fadeLevel < 0) {
        if (GetSubtitleStreamFrame_020a8918() > 0) {
            func_02006748((vu16 *)0x0400006c, 0);
            func_02006748((vu16 *)0x0400106c, 0);
        }
        return;
    }
    if (player->fadeLevel < 16) {
        player->fadeLevel++;
        func_02006748((vu16 *)0x0400006c, -player->fadeLevel);
    }
}
