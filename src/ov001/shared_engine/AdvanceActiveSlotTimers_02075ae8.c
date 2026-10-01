#include "nitro/types.h"

typedef struct SlotState {
    int timer;
    int unk4;
    int unk8;
    int id;
    int mode;
} SlotState;

typedef struct SlotOwner {
    u8 pad[0xd0];
    int count;
} SlotOwner;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern SlotState *func_ov001_02075348(SlotOwner *owner, int index, int create, int flags);

void AdvanceActiveSlotTimers_02075ae8(SlotOwner *owner) {
    SlotState *slot;
    int i;

    if (IsModeSetOrFlag370aClear_0207259c() && !IsHudFlag7Set_020725bc() &&
        !IsFieldFlag10Set_020728c4() && !IsFieldFlag8Set_020728a4()) {
        for (i = 0; i < owner->count; i++) {
            slot = func_ov001_02075348(owner, i, 1, 0);
            if (slot->id != -1 && slot->mode != 3) {
                slot->timer += 2;
            }
        }
    }
}
