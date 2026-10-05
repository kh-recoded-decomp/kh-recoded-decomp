#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s32 elapsed;
    s32 fadeOutDuration;
    s32 fadeInDuration;
} FadeTimer;

int GetFadeInRemainingLevel_020630a4(FadeTimer *timer)
{
    int level = 16 - (timer->elapsed << 4) / timer->fadeInDuration;

    if (level > 16) {
        return 16;
    }
    if (level < 0) {
        level = 0;
    }
    return level;
}
