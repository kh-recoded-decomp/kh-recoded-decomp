#include "nitro/types.h"

typedef struct ReactEntry {
    u8 pad_000[0x1f8];
    void (*setMotion)(struct ReactEntry *entry, int motion, int frame);
    void (*setPose)(struct ReactEntry *entry, int pose);
    u8 pad_200[0x34];
    u32 traits;
    u8 pad_238[0x774];
    u64 stateFlags;
    u8 index;
    u8 pad_9b5[0x43];
    s32 reactTimer;
} ReactEntry;

typedef struct {
    u8 pad_00[0x14];
    int entryIndex;
} ReactOwner;

typedef struct {
    u8 pad_00[0x3d];
    s8 kind;
} ReactSource;

typedef struct {
    u8 pad_00[0x50];
    ReactSource *source;
} ReactActor;

extern ReactEntry *GetBoundedEntryField_0206db5c(int index);
extern int MapKindToSlot_020d7cc4(int kind);
extern void *func_ov052_020d1238(ReactEntry *entry, int *state);
extern void func_ov052_020cef20(ReactEntry *entry);
extern void func_ov052_020cec9c(ReactEntry *entry, int flag);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern void func_ov056_020d316c(void);

void *BeginEntryReaction_020ad064(ReactOwner *owner, ReactActor *actor, int *state) {
    ReactEntry *entry = GetBoundedEntryField_0206db5c(owner->entryIndex);
    u32 heavy = entry->traits & 4;
    int slot = MapKindToSlot_020d7cc4(actor->source->kind);
    int motion;
    if (slot == 8) {
        void *next = func_ov052_020d1238(entry, state);
        if (next != NULL) {
            return next;
        }
        func_ov052_020cef20(entry);
    }
    switch (slot) {
    default:
        motion = 0x1f;
        if (heavy == 0) {
            motion = 0x20;
        }
        break;
    case 2:
        motion = 0x21;
        break;
    case 4:
        motion = 0x22;
        break;
    case 5:
        motion = 0x23;
        break;
    case 6:
        motion = 0x24;
        break;
    case 7:
        motion = 0x25;
        break;
    case 8:
        motion = 0x26;
        break;
    }
    if (entry->setMotion != NULL) {
        entry->setMotion(entry, motion, -1);
    }
    if (entry->setPose != NULL) {
        entry->setPose(entry, 0);
    }
    func_ov052_020cec9c(entry, 0);
    entry->stateFlags |= 0x40;
    *state = 0x1a;
    if (IsPlayerEntryFlagSet_02050014(entry->index, 0x15) && actor->source->kind == 3) {
        entry->reactTimer = 0x3000;
    }
    return func_ov056_020d316c;
}
