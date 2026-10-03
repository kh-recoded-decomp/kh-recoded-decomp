#include "nitro/types.h"

typedef struct {
    u32 state;
    u8 pad_04[0x34];
} RecordEntry;

typedef struct {
    u8 pad_00[0x10];
    void *parent;
} ActorSlot;

typedef struct {
    RecordEntry entries[0x80];
    ActorSlot slot;
} RecordOwner;

extern void func_020366f8(ActorSlot *slot);
extern void ActorSlot_LinkAsRoot_02036710(ActorSlot *slot);
extern void LoadSharedRecordField_020cdf90(RecordOwner *owner);

void InitRecordOwnerSlots_020ce1a8(RecordOwner *owner) {
    int i;

    func_020366f8(&owner->slot);
    if (owner->slot.parent == NULL) {
        ActorSlot_LinkAsRoot_02036710(&owner->slot);
    }
    LoadSharedRecordField_020cdf90(owner);
    for (i = 0; i < 0x80; i++) {
        owner->entries[i].state = 2;
    }
}
