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

extern void G2x_SetBlendAlpha_02006850(vu16 *reg, u32 planeA, u32 planeB, int eva, int evb);

int MovieScene_FadeInBgPlanes_02064154(MovieFadeScene *scene, u32 time, MovieFadeEvent *event)
{
    int step;

    step = ((time - event->startTime) << 4) / event->duration;
    if (scene->visiblePlanes == 0) {
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (event->planeMask << 8);
        if (step >= 16) {
            scene->visiblePlanes = event->planeMask;
            scene->brightness = 0;
            return 1;
        }
        scene->brightness = step - 16;
        return 0;
    }
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((scene->visiblePlanes | event->planeMask) << 8);
    if (step >= 16) {
        scene->visiblePlanes |= event->planeMask;
        REG_BLDCNT = 0;
        return 1;
    }
    G2x_SetBlendAlpha_02006850(&REG_BLDCNT, event->planeMask, scene->visiblePlanes, step, 16 - step);
    return 0;
}
