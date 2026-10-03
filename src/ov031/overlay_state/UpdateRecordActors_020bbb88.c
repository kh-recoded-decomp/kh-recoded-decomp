#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 kind;
    u8 variant;
    s8 offsetX;
    s8 offsetY;
    VecFx32 position;
    u32 param;
} ActorSpawn;

typedef struct {
    u8 pad_00[0x8];
    VecFx32 origin;
    u8 pad_14[0x18];
    ActorSpawn *spawns;
    u8 pad_30[0x9];
    u8 spawnCount;
    u8 pad_3a[0x2];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[0x8];
    ActiveRecord *records;
} OverlayState;

typedef struct {
    u8 pad_00[0x5a];
    u8 category;
} ActorInfo;

typedef struct Actor {
    struct Actor *next;
    ActorInfo *info;
    u8 pad_08[0x38];
    s32 depth;
    u8 pad_44[0xc];
    u16 flags;
} Actor;

extern OverlayState *g_activeState_020bc800;
extern Actor *func_ov001_0208723c(void);
extern s32 func_ov031_020bc700(void);
extern void FieldObject_SetDisabled_020a333c(Actor *actor, int disabled);
extern s8 GetCtxModeByte_02068084(void);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void CallWithZeroFlag_020a3594(Actor *actor, VecFx32 *position, u32 param, int kind, int variant, s8 offsetX, s8 offsetY);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Subtract_01ff9e3c(a, b, &out);
    return out;
}

void UpdateRecordActors_020bbb88(void)
{
    ActiveRecord *record;
    Actor *actor;
    u32 count;
    VecFx32 origin;
    VecFx32 relative;

    record = &g_activeState_020bc800->records[g_activeState_020bc800->recordIndex];
    for (actor = func_ov001_0208723c(); actor != NULL; actor = actor->next) {
        if (actor->info->category == 6 && !(actor->flags & 8) && actor->depth < -func_ov031_020bc700()) {
            FieldObject_SetDisabled_020a333c(actor, 1);
        }
    }
    if (record->spawnCount != 0 && func_ov001_0208723c() != NULL) {
        count = 0;
        for (actor = func_ov001_0208723c(); actor != NULL; actor = actor->next) {
            if (actor->info->category == 6 && (actor->flags & 8)) {
                origin = record->origin;
                if (GetCtxModeByte_02068084() != 6) {
                    ScaleVecFx32InPlace_0204a5e4(&origin, 0x1800);
                }
                relative = SubtractVec(&record->spawns[count].position, &origin);
                CallWithZeroFlag_020a3594(actor, &relative, record->spawns[count].param,
                                          record->spawns[count].kind, record->spawns[count].variant,
                                          record->spawns[count].offsetX, record->spawns[count].offsetY);
                count++;
                if (count == record->spawnCount) {
                    return;
                }
            }
        }
    }
}
