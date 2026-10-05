#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s32 elapsed;
    s32 duration;
} FadeTimer;

int GetFadeProgressLevel_02063044(FadeTimer *timer)
{
    int level = (timer->elapsed << 4) / timer->duration;

    if (level > 16) {
        return 16;
    }
    if (level < 0) {
        level = 0;
    }
    return level;
}
