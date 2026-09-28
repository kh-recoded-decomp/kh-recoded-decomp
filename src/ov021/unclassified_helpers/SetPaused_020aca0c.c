#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x124];
    s32 state;
} StateObj;

void SetPaused_020aca0c(StateObj *obj, s32 paused)
{
    if (paused == 0) {
        if (obj->state == 3) {
            obj->state = 2;
        }
    } else if (obj->state == 2) {
        obj->state = 3;
    }
}
