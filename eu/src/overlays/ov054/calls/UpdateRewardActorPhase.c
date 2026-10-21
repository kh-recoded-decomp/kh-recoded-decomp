#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef void (*EnemyCallback)(Enemy *enemy, int value, int arg);
typedef void (*EnemyNotify)(Enemy *enemy, int value);

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[0x0c];
    s32 timer;
    u8 pad_18[0x12];
    s16 targetIndex;
} AiState;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} TrackRequest;

struct Enemy {
    u8 pad_000[0x1f8];
    EnemyCallback onEnterState;
    EnemyNotify onAnimDone;
    u8 pad_200[0x210 - 0x200];
    EnemyNotify onTurn;
    u8 pad_214[0x230 - 0x214];
    void *model;
    u8 pad_234[0x75c - 0x234];
    s32 animId;
    s32 animFrame;
    u8 pad_764[0x9ac - 0x764];
    u64 stateFlags;
    u8 mode;
    u8 pad_9b5[0xa20 - 0x9b5];
    VecFx32 velocity;
    u8 pad_a2c[0x10ec - 0xa2c];
    EnemyNotify onReset;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern const s16 gSinFx12Table[];

extern void ComputeApproachTarget(VecFx32 *out, int mode);
extern int func_ov058_020d895c(void);
extern int GetSceneSlotAngle(int mode);
extern void func_ov052_020ceb80(Enemy *enemy, VecFx32 *target);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void SetActorPaused(Enemy *enemy, int paused);
extern u16 GetLinkedAngleOffset(Enemy *enemy);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void ResetGaugeDisplay(void);
extern void SetManagerEnabled(BOOL enabled);

static inline void VEC_Set(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/*
 * Moves the reward actor through the presentation phases: in the turning phases it walks to its
 * approach point, turns to its slot angle and plays on until the phase's last frame; in phase 7
 * it is dropped at the point and launched away from its linked actor, then reset to state 4.
 */
void UpdateRewardActorPhase(Enemy *enemy)
{
    VecFx32 target;
    VecFx32 velocity;
    VecFx32 approach;
    int angle;

    ComputeApproachTarget(&approach, enemy->mode);
    target = approach;
    enemy->stateFlags |= 1;
    switch (func_ov058_020d895c()) {
    case 1:
    case 2:
    case 3:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x1d000 && enemy->onAnimDone != NULL) {
            enemy->onAnimDone(enemy, 0);
        }
        break;
    case 4:
    case 5:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x34000 && enemy->onAnimDone != NULL) {
            enemy->onAnimDone(enemy, 0x30000);
        }
        break;
    case 7:
        Obj_SetPosition(enemy->model, &target);
        SetActorPaused(enemy, 0);
        enemy->stateFlags &= ~0x1000000ULL;
        angle = (u16)(GetLinkedAngleOffset(enemy) + 0x8000) >> 4;
        VEC_Set(&velocity, 0, 0, 0);
        velocity.x = -gSinFx12Table[angle];
        velocity.z = -gSinFx12Table[(0x400 - angle) & 0xfff];
        ScaleVecFx32(0x1000, &velocity, &velocity);
        enemy->velocity = velocity;
        enemy->onReset(enemy, 4);
        ResetGaugeDisplay();
        SetManagerEnabled(FALSE);
        enemy->stateFlags &= ~0x200000000ULL;
        break;
    case 6:
        func_ov052_020ceb80(enemy, &target);
        angle = GetSceneSlotAngle(enemy->mode);
        if (enemy->onTurn != NULL) {
            enemy->onTurn(enemy, angle);
        }
        if (enemy->animFrame >= 0x48000) {
            SetActorPaused(enemy, 1);
        }
        break;
    }
}
