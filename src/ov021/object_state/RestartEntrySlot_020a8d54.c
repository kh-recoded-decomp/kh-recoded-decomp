#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
    u8 tracks[0x10c];
    u32 soundHandle;
    u8 pad_118[0x20];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
} EntryGroup;

extern BOOL g_groupsReady_020b5608;
extern EntryGroup *FindEntryGroupById_020a8810(int groupId);
extern int *func_01ffb2f8(void *state, int track, int frame);
extern void func_ov021_020a8844(VecFx32 *out, EntrySlot *slot);
extern int func_ov001_02063a38(void);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u16 flags);

void RestartEntrySlot_020a8d54(int groupId, int index, int soundOwner, int soundKind)
{
    EntryGroup *group;
    EntrySlot *slot;
    VecFx32 anchor;
    VecFx32 position;
    int flags;

    FindEntryGroupById_020a8810(groupId);
    if (g_groupsReady_020b5608 == 0) {
        return;
    }
    group = FindEntryGroupById_020a8810(groupId);
    if (group == NULL) {
        return;
    }
    slot = &group->slots[index];
    if (slot->inUse == 1) {
        func_01ffb2f8(slot->tracks, 0, 0);
        func_01ffb2f8(slot->tracks, 1, 0);
        func_01ffb2f8(slot->tracks, 2, 0);
        func_01ffb2f8(slot->tracks, 4, 0);
        func_01ffb2f8(slot->tracks, 3, 0);
    }
    if (soundOwner == -1 || soundKind == -1) {
        return;
    }
    func_ov021_020a8844(&position, slot);
    anchor = position;
    flags = 0;
    if (func_ov001_02063a38() != 4 && slot->anchorMode != 0) {
        flags |= 5;
    }
    slot->soundHandle = SpawnSoundSlot_0204da8c(soundOwner, soundKind, &anchor, flags);
}
