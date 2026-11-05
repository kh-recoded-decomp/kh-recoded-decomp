#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 team;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
} HitParams;

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[0x0c];
    s32 timer;
    u8 pad_18[0x12];
    s16 hitStatus;
} AiState;

typedef struct Enemy Enemy;

struct Enemy {
    u8 pad_0000[0x230];
    void *object;
    u8 pad_0234[0x9ac - 0x234];
    u64 statusFlags;
    u8 team;
    u8 pad_09b5[0x10ec - 0x9b5];
    void (*onEvent)(Enemy *enemy, s32 event);
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern void Enemy_ClearTargetKindAndArrivalFlag(Enemy *enemy);
extern void ResetAnimationTrackState(HitParams *params);
extern s16 func_ov021_020a8cc0(HitParams *params, s32 effectId);
extern VecFx32 *GetActorModelPosition(Enemy *enemy);
extern s32 GetFieldEntryGroupId(s32 index);
extern void Obj_RemoveFromQuadTree(void *object);

void Enemy_SpawnEvent1EEffectAndDetachCollider(Enemy *enemy)
{
    AiState *ai = &enemy->ai;
    HitParams params;

    enemy->onEvent(enemy, 0x1e);
    ai->flags &= ~0x80000;
    Enemy_ClearTargetKindAndArrivalFlag(enemy);
    enemy->statusFlags |= 0x60000;
    ResetAnimationTrackState(&params);
    params.team = enemy->team;
    params.unk_25 = 0;
    params.unk_24 = 0;
    params.position = *GetActorModelPosition(enemy);
    ai->hitStatus = func_ov021_020a8cc0(&params, GetFieldEntryGroupId(7));
    ai->timer = 0;
    Obj_RemoveFromQuadTree(enemy->object);
}
