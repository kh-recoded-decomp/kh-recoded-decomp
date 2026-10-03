#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundPair {
    u16 seqArcId;
    u16 soundId;
} SoundPair;

typedef struct SoundTable {
    u8 pad_00[0xc4];
    u32 count;
    u32 stride;
    u8 *entries;
} SoundTable;

typedef struct SoundBank {
    u8 pad_00[8];
    SoundTable *table;
} SoundBank;

typedef struct SoundOwner {
    u8 pad_00[4];
    SoundBank *bank;
} SoundOwner;

typedef struct AlternatingState {
    u8 pad_00[6];
    u16 pad_bits : 4;
    u16 primaryToggle : 1;
    u16 secondaryToggle : 1;
} AlternatingState;

typedef struct SoundEmitter {
    u8 pad_000[0x2c0];
    VecFx32 position;
} SoundEmitter;

extern u32 PlayStageSoundAt_0209d080(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

static inline u32 GetSoundCount(SoundOwner *owner) {
    if (owner == NULL) {
        return 0;
    }
    if (owner->bank == NULL) {
        return 0;
    }
    return owner->bank->table->count;
}

static inline SoundPair *GetSoundPair(SoundOwner *owner, int index) {
    u32 count;
    SoundTable *table;
    u8 *entries;
    if (owner == NULL) {
        return NULL;
    }
    if (owner->bank == NULL) {
        return NULL;
    }
    count = GetSoundCount(owner);
    table = owner->bank->table;
    entries = table->entries;
    if (count == 0) {
        return NULL;
    }
    if (count <= (u16)index) {
        return NULL;
    }
    return (SoundPair *)(entries + (u16)index * table->stride);
}

void PlayAlternatingStageSound_0209279c(AlternatingState *state, SoundEmitter *emitter, SoundOwner *owner, BOOL secondary) {
    u16 index;
    SoundPair *pair;

    if (owner == NULL) {
        return;
    }
    if (secondary) {
        index = state->secondaryToggle + 2;
        state->secondaryToggle = !state->secondaryToggle;
        state->primaryToggle = 0;
    } else {
        index = state->primaryToggle;
        state->primaryToggle = !index;
        state->secondaryToggle = 0;
    }
    pair = GetSoundPair(owner, index);
    if (pair != NULL) {
        PlayStageSoundAt_0209d080(pair->seqArcId, pair->soundId, &emitter->position, 0);
    }
}
