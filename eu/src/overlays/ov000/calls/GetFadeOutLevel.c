#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s32 elapsed;
    s32 duration;
} FadeTimer;

int GetFadeOutLevel(FadeTimer *timer)
{
    int level = -(timer->elapsed << 4) / timer->duration;

    if (level > 0) {
        return 0;
    }
    if (level < -16) {
        level = -16;
    }
    return level;
}
