#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    u8 doubled;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x90];
} AnimEntry;

typedef struct {
    u8 pad_00[8];
    s32 prevIndex;
    u8 pad_0c[0x50];
    s32 lowHeight;
    s32 highHeight;
    u8 pad_64[8];
    AnimEntry *entries;
    u8 pad_70[0xc];
    s16 *groupId;
    s8 highSlot;
    s8 lowSlot;
} AnimRecord;

typedef struct {
    u8 data[0x20];
} SlotEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x234];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 height;
    u8 pad_764[4];
    s32 active;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9ec - 0x9b5];
    s32 slotTarget;
    u8 pad_9f0[0xa51 - 0x9f0];
    s8 animIndex;
    u8 pad_a52[0x1078 - 0xa52];
    AnimRecord *record;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(Actor *actor, int state);
};

extern void func_ov052_020cfdb4(Actor *actor, AnimEntry *entry, int arg);
extern void ApplyAnimRootMotion_020cff8c(Actor *actor, AnimEntry *entry);
extern void InitSlotEntryFromRecord_020d1a68(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern int ProcessTargetHitEntries_020d012c(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL UpdateActionPhase_020d0294(Actor *actor, AnimEntry *data, int which);
extern int func_ov052_020d03b8(Actor *actor);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern void SetGroupSlotTarget_020a8ea8(int groupId, int index, s32 target);

void UpdateRisingEffectSlots_020d36dc(Actor *actor)
{
    SlotEntry slot;
    MarkerRequest request;
    AnimRecord *record;
    AnimEntry *entries;
    int groupId;
    u32 stateFlags;
    int animIndex;

    record = actor->record;
    entries = record->entries;
    animIndex = actor->animIndex;
    func_ov052_020cfdb4(actor, &entries[animIndex], 0);
    ApplyAnimRootMotion_020cff8c(actor, &entries[animIndex]);
    InitSlotEntryFromRecord_020d1a68(&slot, &entries[animIndex], 0, record, actor->player);
    groupId = *record->groupId;
    if (record->lowSlot == -1) {
        if (actor->height >= record->lowHeight) {
            func_ov021_020a8ab4(&request);
            request.id = actor->player;
            request.unk_25 = 1;
            request.angle = 0x8000;
            request.doubled = 0;
            request.prevIndex = record->prevIndex;
            request.index = 0;
            record->lowSlot = func_ov021_020a8ca0(&request, groupId);
        }
    } else {
        SetGroupSlotTarget_020a8ea8(groupId, record->lowSlot, actor->slotTarget);
    }
    if (record->highSlot == -1) {
        if (actor->height >= record->highHeight) {
            func_ov021_020a8ab4(&request);
            request.id = actor->player;
            request.unk_25 = 1;
            request.angle = 0x8000;
            request.doubled = 1;
            request.prevIndex = record->prevIndex;
            request.index = 1;
            record->highSlot = func_ov021_020a8ca0(&request, groupId);
        }
    } else {
        SetGroupSlotTarget_020a8ea8(groupId, record->highSlot, actor->slotTarget);
    }
    if (ProcessTargetHitEntries_020d012c(actor, &entries[animIndex], &slot)) {
        return;
    }
    if (UpdateActionPhase_020d0294(actor, &entries[animIndex], 0)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    stateFlags = actor->stateFlags & 4;
    if (func_ov052_020d03b8(actor)) {
        return;
    }
    if (stateFlags) {
        actor->setState(actor, 5);
    } else {
        actor->setState(actor, 4);
    }
}
