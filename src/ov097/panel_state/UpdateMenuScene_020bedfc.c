#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0xf078];
    int frameCounter;
    int blinkPhase;
    int waveAngle;
} MenuScene;

extern void (*const data_ov097_020c1da4[])(void);
extern s16 data_0205356c[];
extern int func_ov097_020c1570(MenuScene *scene);
extern void func_ov097_020bfb38(int mode, MenuScene *scene);
extern void func_ov097_020c0ef8(MenuScene *scene);
extern void InitSlotPools_020bff74(MenuScene *scene);
extern void DrawScrolledPopups_020c0d70(MenuScene *scene);
extern int GetScrollTrackRow_020c13a8(int trackIndex);
extern void SetScrollTrackTarget_020c1328(int trackIndex, int row);
extern void EaseScrollTrack_020c13c8(int trackIndex);

void UpdateMenuScene_020bedfc(MenuScene *scene)
{
    void (*handler)(void) = data_ov097_020c1da4[func_ov097_020c1570(scene)];
    fx32 wave;

    if (handler != NULL) {
        handler();
    }
    if (++scene->frameCounter >= 60) {
        scene->frameCounter = 0;
        scene->blinkPhase = (scene->blinkPhase + 1) % 2;
        func_ov097_020bfb38(0, scene);
    }
    func_ov097_020c0ef8(scene);
    InitSlotPools_020bff74(scene);
    DrawScrolledPopups_020c0d70(scene);
    *(vu32 *)0x04001010 = (GetScrollTrackRow_020c13a8(0) << 16) & 0x01ff0000;
    scene->waveAngle += 0xb4;
    if (scene->waveAngle >= 0x8000) {
        scene->waveAngle -= 0x8000;
    }
    wave = (fx32)(((s64)data_0205356c[scene->waveAngle >> 4] * 0x8000 + 0x800) >> 12);
    SetScrollTrackTarget_020c1328(0, wave >> 12);
    EaseScrollTrack_020c13c8(0);
}
