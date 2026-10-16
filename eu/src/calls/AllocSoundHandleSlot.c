#include "nitro/types.h"
#include "nitro/fx_types.h"

/* Adapted from khdays-decomp/src/engine/ScriptPool_AllocSlot.c (CC0-1.0). */
typedef struct SoundHandleSlot {
    struct SoundHandleSlot *next;
    struct SoundHandleSlot *previous;
    VecFx32 position;
    u16 flags;
    s16 playerIndex;
    u32 id;
    void *player;
} SoundHandleSlot;

typedef struct SoundWorkView {
    u8 reserved00000[0xb4718];
    SoundHandleSlot *freeSlots;
    SoundHandleSlot *activeSlots;
    u8 reservedb4720[0xb47d4 - 0xb4720];
    u8 muted;
} SoundWorkView;

enum {
    SOUND_SLOT_ACTIVE = 1,
    SOUND_SLOT_MUTED = 4,
    SOUND_SLOT_ID_MASK = 0x00ffffff
};

typedef char SoundHandleSlotSizeCheck[sizeof(SoundHandleSlot) == 0x20 ? 1 : -1];
#define SOUND_OFFSET_OF(type, member) ((u32)&((type *)0)->member)
typedef char SoundSlotFlagsOffsetCheck[SOUND_OFFSET_OF(SoundHandleSlot, flags) == 0x14 ? 1 : -1];
typedef char SoundSlotIdOffsetCheck[SOUND_OFFSET_OF(SoundHandleSlot, id) == 0x18 ? 1 : -1];
typedef char SoundFreeListOffsetCheck[SOUND_OFFSET_OF(SoundWorkView, freeSlots) == 0xb4718 ? 1 : -1];
typedef char SoundActiveListOffsetCheck[SOUND_OFFSET_OF(SoundWorkView, activeSlots) == 0xb471c ? 1 : -1];
typedef char SoundMuteOffsetCheck[SOUND_OFFSET_OF(SoundWorkView, muted) == 0xb47d4 ? 1 : -1];
#undef SOUND_OFFSET_OF

extern SoundWorkView *gSoundWork;
extern u32 gSoundRequestSerial;

s32 AllocSoundHandleSlot(void)
{
    SoundWorkView *work = gSoundWork;
    SoundHandleSlot *slot = work->freeSlots;
    u32 flags;

    if (slot == NULL) {
        return 0;
    }
    work->freeSlots = slot->next;
    if (slot->next != NULL) {
        slot->next->previous = NULL;
    }
    slot->next = work->activeSlots;
    slot->previous = NULL;
    if (work->activeSlots != NULL) {
        work->activeSlots->previous = slot;
    }
    work->activeSlots = slot;
    flags = SOUND_SLOT_ACTIVE | SOUND_SLOT_MUTED;
    if (!work->muted) {
        flags = SOUND_SLOT_ACTIVE;
    }
    slot->flags = flags;
    {
        /* The repeated assignment preserves CodeWarrior's original instruction order. */
        unsigned long id = slot->id = gSoundRequestSerial++ & SOUND_SLOT_ID_MASK;
        slot->id = id;
    }
    return (s32)slot;
}
