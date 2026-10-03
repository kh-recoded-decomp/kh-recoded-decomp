#include "nitro/types.h"

typedef struct {
    u32 timedParam;
    s32 groupBase;
} SlotDefault;

typedef struct {
    SlotDefault entries[3];
} SlotDefaults;

typedef struct {
    s32 effect;
    s32 timed;
    u32 value;
} SlotDesc;

typedef struct {
    u32 id;
    u32 mode;
    SlotDesc slots[3];
    s32 duration;
    s32 limit;
    u32 extra;
} EffectSlotDesc;

typedef struct {
    u8 pad_00[4];
    u32 *idOut;
    s16 handles[3];
    u8 pad_0e[2];
    u32 values[3];
    s32 duration;
    s32 limit;
    u32 extra;
    u32 mode;
} EffectSlotState;

typedef struct {
    u8 pad_00[0x40];
    EffectSlotState state;
    u8 pad_6c[8];
    s16 *slotPtrs[3];
} EffectSlotOwner;

extern const SlotDefaults data_ov021_020b4ff4;
extern s16 *EnsureEffectGroup_020acb6c(void *context, int slot);
extern s16 CreateTimedEntryPair_020acc00(void *context, u32 index, u32 param, int extra);

void SetupEffectSlots_020ad384(EffectSlotOwner *owner, void *context, s32 *src) {
    EffectSlotDesc desc;
    SlotDefaults defaults = data_ov021_020b4ff4;
    EffectSlotState *state = &owner->state;
    int i;
    desc.id = src[0];
    desc.mode = src[1];
    src += 2;
    for (i = 0; i < 3; i++) {
        desc.slots[i].effect = src[0];
        desc.slots[i].timed = src[1];
        desc.slots[i].value = src[2];
        src += 3;
    }
    desc.duration = src[0];
    desc.limit = src[1];
    desc.extra = src[2];
    *state->idOut = desc.id;
    for (i = 0; i < 3; i++) {
        if (desc.slots[i].effect >= 0) {
            owner->slotPtrs[i] = EnsureEffectGroup_020acb6c(context, defaults.entries[i].groupBase + desc.slots[i].effect);
        } else if (desc.slots[i].timed >= 0) {
            state->handles[i] = CreateTimedEntryPair_020acc00(context, desc.slots[i].timed, defaults.entries[i].timedParam, 0);
            owner->slotPtrs[i] = &state->handles[i];
        }
        state->values[i] = desc.slots[i].value;
    }
    state->duration = desc.duration << 12;
    state->limit = desc.limit > 0 ? desc.limit << 12 : 0x7fffffff;
    state->extra = desc.extra;
    state->mode = desc.mode;
}
