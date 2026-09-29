#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundSlot {
    u8 flags;
    u8 handleId;
} SoundSlot;

typedef struct SoundActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
    u8 pad_2cc[0x33a - 0x2cc];
    u16 soundNodeId;
    u8 pad_33c[0x3b4 - 0x33c];
    SoundSlot soundSlots[8];
} SoundActor;

typedef struct SoundHandleEntry {
    u16 bank;
    u16 soundId;
    u32 handle;
} SoundHandleEntry;

extern void func_ov001_02091600(SoundActor *actor, u16 nodeId, VecFx32 *position);
extern void func_ov001_0209d080(u16 bank, u16 soundId, VecFx32 *position, u16 volume);
extern u8 func_ov001_0209d0e8(u16 bank, u16 soundId, VecFx32 *position, u16 volume);
extern SoundHandleEntry *GetStageEntrySlot_0209c1fc(u32 id);
extern void ReleaseSlotResource_0209d15c(u32 id);

void PlayActorSound_02091b24(SoundActor *actor, u16 bank, u16 soundId, u32 flags, u16 volume)
{
    VecFx32 position;
    u8 handleId;
    s32 freeSlot;
    SoundSlot *slot;
    int i;
    SoundHandleEntry *entry;

    if (bank == 0 && soundId == 0) {
        return;
    }
    if (bank == 0) {
        if (soundId == 0x25) {
            flags |= 1;
        }
        if (soundId == 0x26) {
            flags |= 1;
        }
        if (soundId == 0x2d) {
            flags |= 1;
        }
    }
    if (actor->soundNodeId != 0) {
        func_ov001_02091600(actor, actor->soundNodeId, &position);
    } else {
        position = actor->position;
    }
    if (flags & 1) {
        func_ov001_0209d080(bank, soundId, &position, volume);
        return;
    }
    handleId = func_ov001_0209d0e8(bank, soundId, &position, volume);
    if (handleId == 0) {
        return;
    }
    freeSlot = -1;
    for (i = 0; i < 8; i++) {
        slot = &actor->soundSlots[i];
        if (slot->handleId == 0) {
            if (freeSlot < 0) {
                slot->handleId = handleId;
                slot->flags = 0;
                if (flags & 4) {
                    slot->flags |= 4;
                }
                freeSlot = 0;
            }
        } else if (flags & 2) {
            entry = GetStageEntrySlot_0209c1fc(slot->handleId);
            if (entry != NULL && entry->handle != 0 && entry->bank == bank && entry->soundId == soundId) {
                ReleaseSlotResource_0209d15c(slot->handleId);
            }
        }
    }
}
