#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageManager {
    u8 pad_00000[0x18f2c];
    s8 fadeStartBrightness;
    s8 fadeTargetBrightness;
    u8 pad_18f2e[2];
    fx32 fadeTime;
    fx32 fadeDuration;
} StageManager;

extern StageManager *g_stageManager_020a0508;
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void SetBrightnessAndSyncMain_02029e7c(int value);

void UpdateStageBrightnessFade_0209b8e0(void)
{
    StageManager *manager = g_stageManager_020a0508;
    s8 delta;

    if (manager->fadeDuration != 0) {
        manager->fadeTime += 0x1000;
        if (manager->fadeTime <= manager->fadeDuration) {
            fx32 progress = FX_Div_01ff9c84(manager->fadeTime, manager->fadeDuration);
            delta = manager->fadeTargetBrightness - manager->fadeStartBrightness;
            SetBrightnessAndSyncMain_02029e7c((s8)(manager->fadeStartBrightness + (s8)((delta * progress) >> 12)));
            return;
        }
        manager->fadeDuration = 0;
        SetBrightnessAndSyncMain_02029e7c(manager->fadeTargetBrightness);
        return;
    }
    if (manager->fadeTargetBrightness != 0) {
        SetBrightnessAndSyncMain_02029e7c(manager->fadeTargetBrightness);
    }
}
