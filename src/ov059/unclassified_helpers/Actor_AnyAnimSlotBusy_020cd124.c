#include "nitro/types.h"

typedef struct {
    u8 data[0x230];
} AnimSlot;

typedef struct {
    u8 pad_000[0x9d4];
    AnimSlot slots[2];
} Actor;

extern BOOL func_ov021_020a9d04(AnimSlot *slot);

BOOL Actor_AnyAnimSlotBusy_020cd124(Actor *actor)
{
    BOOL found = FALSE;
    int i;

    for (i = 0; i < 2; i++) {
        if (func_ov021_020a9d04(&actor->slots[i])) {
            found = TRUE;
            break;
        }
    }
    return found;
}
