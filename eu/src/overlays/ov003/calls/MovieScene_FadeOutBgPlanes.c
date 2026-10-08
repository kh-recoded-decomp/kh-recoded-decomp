#include "nitro/types.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BLDCNT (*(vu16 *)0x04000050)

typedef struct MovieFadeEvent {
    u32 startTime;
    u16 unused4;
    u16 planeMask;
    u16 duration;
} MovieFadeEvent;

typedef struct MovieFadeScene {
    u8 pad_000[0x8c8];
    u8 visiblePlanes;
    u8 pad_8c9[3];
    int brightness;
} MovieFadeScene;

extern void G2x_SetBlendAlpha_(vu16 *reg, u32 planeA, u32 planeB, int eva, int evb);

int MovieScene_FadeOutBgPlanes(MovieFadeScene *scene, u32 time, MovieFadeEvent *event)
{
    int step;
    u32 remaining;

    step = ((time - event->startTime) << 4) / event->duration;
    remaining = scene->visiblePlanes & ~event->planeMask;
    if (remaining == 0) {
        if (step < 16) {
            scene->brightness = -step;
            return 0;
        }
        REG_DISPCNT &= ~0x1f00;
        scene->visiblePlanes = 0;
        scene->brightness = -16;
        return 1;
    }
    if (step >= 16) {
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((scene->visiblePlanes &= ~event->planeMask) << 8);
        REG_BLDCNT = 0;
        return 1;
    }
    G2x_SetBlendAlpha_(&REG_BLDCNT, remaining, event->planeMask, step, 16 - step);
    return 0;
}
