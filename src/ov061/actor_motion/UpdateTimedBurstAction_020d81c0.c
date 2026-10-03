#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    u8 stage;
    u8 visible;
    u8 pad_26[6];
} MarkerRequest;

typedef struct {
    u8 pad_00[0x90];
} AnimEntry;

typedef struct {
    u8 pad_00[0x6c];
    AnimEntry *entries;
    u8 pad_70[4];
    void *hitSource;
    u8 pad_78[4];
    s16 *groupId;
    u8 pad_80[8];
    u32 spawnedMask;
} AnimRecord;

typedef struct {
    void (*callback)();
    AnimRecord *context;
    u8 pad_08[0x10];
    u16 flags;
    u8 pad_1a[6];
} SlotEntry;

typedef struct {
    s32 frames[4];
} BurstSchedule;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x210];
    void (*setFacing)(Actor *actor, u16 angle);
    u8 pad_214[0x228 - 0x214];
    BOOL (*getTargetPosition)(Actor *actor, VecFx32 *out);
    u8 pad_22c[0x234 - 0x22c];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 active;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0xa51 - 0x9b5];
    s8 animIndex;
    u8 pad_a52[0x1078 - 0xa52];
    AnimRecord *record;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setState)(Actor *actor, int state);
};

extern const BurstSchedule data_ov061_020d8500;

extern void ApplyAnimRootMotion_020cff8c(Actor *actor, AnimEntry *entry);
extern void InitSlotEntryFromRecord_020d1a68(SlotEntry *entry, void *source, int mirrored, AnimRecord *record, int player);
extern void SpawnGroupHitMarker_020d3c30();
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern void ForwardSubModePairA_020af544(int first, int second);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(int vertical, int horizontal);
extern int ProcessTargetHitEntries_020d012c(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL UpdateActionPhase_020d0294(Actor *actor, AnimEntry *data, int which);
extern void ResetGaugeDisplay_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);

void UpdateTimedBurstAction_020d81c0(Actor *actor)
{
    AnimRecord *record = actor->record;
    AnimEntry *entry = &record->entries[actor->animIndex];
    SlotEntry slot;
    BurstSchedule schedule;
    MarkerRequest request;
    VecFx32 target;
    VecFx32 diff;
    u32 flags;
    int i;

    ApplyAnimRootMotion_020cff8c(actor, entry);
    InitSlotEntryFromRecord_020d1a68(&slot, entry, 0, record, actor->player);
    slot.flags |= 4;
    if (record->hitSource != NULL) {
        slot.callback = SpawnGroupHitMarker_020d3c30;
        slot.context = record;
    }
    schedule = data_ov061_020d8500;
    for (i = 0; i < 4; i++) {
        u32 bit = 1 << i;
        if (!(record->spawnedMask & bit) && actor->frame >= schedule.frames[i]) {
            BOOL found;

            func_ov021_020a8ab4(&request);
            request.id = actor->player;
            request.visible = 1;
            request.angle = 0x8000;
            request.stage = i + 1;
            func_ov021_020a8ca0(&request, *record->groupId);
            record->spawnedMask |= bit;
            if (i == 3) {
                ForwardSubModePairA_020af544(3, 0);
            }
            if (actor->getTargetPosition != NULL) {
                found = actor->getTargetPosition(actor, &target);
            } else {
                found = FALSE;
            }
            if (found) {
                int angle;

                VEC_Subtract_01ff9e3c(&target, func_ov052_020ceb54(actor), &diff);
                angle = (u16)(FixedPointAtan2_020062bc(diff.x, diff.z) + 0x8000);
                if (actor->setFacing != NULL) {
                    actor->setFacing(actor, angle);
                }
            }
        }
    }
    if (ProcessTargetHitEntries_020d012c(actor, entry, &slot)) {
        return;
    }
    if (UpdateActionPhase_020d0294(actor, entry, 0)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    flags = actor->stateFlags & 4;
    ResetGaugeDisplay_020734f8();
    SetManagerEnabled_0206e160(0);
    if (flags) {
        actor->setState(actor, 5);
    } else {
        actor->setState(actor, 4);
    }
}
