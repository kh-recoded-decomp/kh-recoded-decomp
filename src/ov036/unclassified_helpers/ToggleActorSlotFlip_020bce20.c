#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x26];
    u16 flipFlags;
    u8 pad_28[0x74];
} SlotEntry;

typedef struct SlotScene {
    u8 pad_0000[0x1090];
    SlotEntry *slots;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3920;
extern int FindOrAcquireOwnerSlot_020bb7c0(int ownerId);

void ToggleActorSlotFlip_020bce20(int ownerId)
{
    SlotScene *scene = data_ov036_020c3920.scene;
    SlotEntry *slot = &scene->slots[FindOrAcquireOwnerSlot_020bb7c0(ownerId)];

    slot->flipFlags = slot->flipFlags == 0 ? 0x8000 : 0;
}
