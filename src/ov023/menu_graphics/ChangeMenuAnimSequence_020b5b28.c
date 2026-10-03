#include "nitro/types.h"

typedef struct MenuAnimSlot {
    int slot;
    int sequence;
} MenuAnimSlot;

extern void SetSlotAnimSequence_0204f24c(void *owner, int slot, int sequence, u32 mode);
extern void func_0204f178(void *owner, int slot, u8 mode);

void ChangeMenuAnimSequence_020b5b28(void *owner, MenuAnimSlot *anim, int sequence, u32 mode)
{
    if (anim->sequence != sequence) {
        SetSlotAnimSequence_0204f24c(owner, anim->slot, sequence, mode);
        anim->sequence = sequence;
        func_0204f178(owner, anim->slot, mode);
    }
}
