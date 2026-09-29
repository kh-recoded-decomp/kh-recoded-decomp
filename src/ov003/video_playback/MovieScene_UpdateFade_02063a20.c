#include "nitro/types.h"

#define REG_MASTER_BRIGHT_MAIN ((vu16 *)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((vu16 *)0x0400106c)

typedef struct MovieScene {
    u8 pad_000[0x8bc];
    BOOL fadeToWhite;
    s32 fadeStep;
    u8 pad_8c4[0x08];
    s32 mainBrightnessLimit;
} MovieScene;

extern int MoviePlayer_GetFrameCount_020a8918(void);
extern void SetMasterBrightness_02006748(vu16 *reg, int brightness);

void MovieScene_UpdateFade_02063a20(MovieScene *scene)
{
    int level;

    if (scene->fadeStep < 0) {
        if (MoviePlayer_GetFrameCount_020a8918() <= 0) {
            return;
        }
        SetMasterBrightness_02006748(REG_MASTER_BRIGHT_SUB, 0);
        return;
    }
    if (scene->fadeStep >= 16) {
        return;
    }
    level = ++scene->fadeStep;
    if (!scene->fadeToWhite) {
        level = -level;
    }
    SetMasterBrightness_02006748(REG_MASTER_BRIGHT_SUB, level);
    if (level >= scene->mainBrightnessLimit) {
        level = scene->mainBrightnessLimit;
    }
    SetMasterBrightness_02006748(REG_MASTER_BRIGHT_MAIN, level);
}
