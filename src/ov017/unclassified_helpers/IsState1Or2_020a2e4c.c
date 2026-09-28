#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4a];
    s8 state;
} OverlayObject;

BOOL IsState1Or2_020a2e4c(OverlayObject *obj)
{
    return obj->state == 2 || obj->state == 1;
}
