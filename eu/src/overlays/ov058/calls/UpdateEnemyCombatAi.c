#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef u32 (*EnemyFlagGetter)(Enemy *enemy);
typedef BOOL (*EnemyQuery)(Enemy *enemy, int arg);

/* What the AI asks of the enemy this frame. */
typedef struct EnemyCommand {
    u8 pad_00[0xc];
    u16 actions;
    u16 moveFlags;
    u16 arrived;
} EnemyCommand;

typedef struct AiState {
    s32 mode;
    u32 flags;
    u8 pad_08[4];
    s32 kind;
    u8 pad_10[4];
    s32 timer;
    fx32 retreatTimer;
    u8 pad_1c[4];
    fx32 alertTimer;
    u8 pad_24[4];
    u16 result;
} AiState;

/* The point the enemy waits at, shared with its partner. */
typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    u16 eventId;
    u8 pad_06[2];
    VecFx32 position;
} WaitTarget;

typedef struct StageEventTargetInfo {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[8];
    s32 count;
    u8 pad_20[4];
} StageEventTargetInfo;

typedef struct ObjHandle {
    u8 pad_00[0x60];
    void *active;
} ObjHandle;

struct Enemy {
    u8 pad_000[0x21c];
    EnemyFlagGetter getMoveFlags;
    u8 pad_220[0x228 - 0x220];
    EnemyQuery canShareTarget;
    u8 pad_22c[0x234 - 0x22c];
    u32 behaviorFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 mode;
    u8 pad_9b5[0xa18 - 0x9b5];
    s32 turnSpeed;
    u8 pad_a1c[0xfc8 - 0xa1c];
    ObjHandle objHandle;
    u8 pad_102c[0x1034 - 0x102c];
    s8 partnerSlot;
    u8 pad_1035[0x1048 - 0x1035];
    WaitTarget waitTarget;
    u8 pad_105c[0x1258 - 0x105c];
    AiState ai;
};

extern Enemy *data_ov058_020d8a40;
extern const VecFx32 data_ov058_020d896c;

extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);
extern Enemy *GetBoundedEntryField(int index);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_ov001_0206db44(void);
extern void func_ov058_020d503c(Enemy *enemy);
extern void func_ov058_020d50cc(Enemy *enemy);
extern BOOL IsFacedByPlayer(Enemy *enemy, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL SteerEnemyTowardPoint(Enemy *enemy, EnemyCommand *command, const VecFx32 *dest, BOOL checkStuck);
extern void func_ov058_020d4ffc(Enemy *enemy, EnemyCommand *command);
extern void func_ov058_020d4a54(Enemy *enemy, EnemyCommand *command);
extern void UpdateEnemyTargetTracking(Enemy *enemy, EnemyCommand *command);
extern void RefreshAiModeFromFlags(Enemy *enemy, EnemyCommand *command);
extern BOOL IsWaitTargetReady(WaitTarget *target);
extern VecFx32 *GetWaitTargetPosition(WaitTarget *target);
extern BOOL HasReachedMoveTarget(Enemy *enemy, VecFx32 *point);
extern BOOL func_ov058_020d4968(Enemy *enemy, VecFx32 *point);
extern BOOL IsObjHandleOverLimit(ObjHandle *handle);
extern BOOL GetStageEventTargetInfo(u16 eventId, StageEventTargetInfo *info);

#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : ((x) < (lo) ? (lo) : (x)))

static inline u32 Enemy_GetMoveFlags(Enemy *enemy)
{
    if (enemy->getMoveFlags != NULL) {
        return enemy->getMoveFlags(enemy);
    }
    return 0;
}

static inline BOOL Enemy_CanShareTarget(Enemy *enemy)
{
    if (enemy->canShareTarget != NULL) {
        return enemy->canShareTarget(enemy, 0);
    }
    return FALSE;
}

/*
 * One AI tick of an enemy that fights around the player: ticks its alert and retreat timers,
 * then by mode flanks the player while it faces it (4), circles it (3), waits (2), joins its
 * partner's wait point (6) or walks to its own wait point (5); otherwise it tracks the player.
 * Every mode but waiting ends by refreshing the mode from the flags.
 */
u16 UpdateEnemyCombatAi(Enemy *enemy, EnemyCommand *command)
{
    AiState *ai = &enemy->ai;
    VecFx32 *pos = func_ov052_020ceb74(enemy);
    VecFx32 *playerPos;
    fx32 range;
    fx32 distance;

    range = 0x14000;
    if (ai->kind == 4) {
        range = 0xa000;
    }
    data_ov058_020d8a40 = GetBoundedEntryField(0);
    playerPos = func_ov052_020ceb74(data_ov058_020d8a40);
    distance = VEC_Distance(playerPos, pos);
    ai->alertTimer = CLAMP(ai->alertTimer - func_ov001_0206db44(), 0, 0x1e000);
    ai->retreatTimer = CLAMP(ai->retreatTimer - func_ov001_0206db44(), 0, 0x1e000);
    func_ov058_020d503c(enemy);
    if (enemy->stateFlags & 0x20820) {
        return 0;
    }
    if (ai->flags & 0x100000) {
        return 0;
    }
    switch (ai->mode) {
    case 4: {
        VecFx32 target = *playerPos;

        if (IsFacedByPlayer(enemy, &target)) {
            VEC_MultAdd(0x3000, &target, pos, &target);
            enemy->turnSpeed = 0x19a;
            if (SteerEnemyTowardPoint(enemy, command, &target, TRUE) || range < distance) {
                if (!(Enemy_GetMoveFlags(data_ov058_020d8a40) & 8)) {
                    func_ov058_020d50cc(enemy);
                }
            }
        }
        func_ov058_020d4ffc(enemy, command);
        RefreshAiModeFromFlags(enemy, command);
        break;
    }
    case 3: {
        VecFx32 up = data_ov058_020d896c;
        VecFx32 side;
        VecFx32 toPlayer;
        VecFx32 dir;
        BOOL checkStuck = TRUE;

        VEC_Subtract(playerPos, func_ov052_020ceb74(enemy), &toPlayer);
        VEC_Normalize(&toPlayer, &dir);
        VEC_CrossProduct(&dir, &up, &side);
        if (enemy->mode >= 2) {
            {
                fx32 z = -side.z;
                fx32 y = -side.y;
                fx32 x = -side.x;

                side.x = x;
                side.y = y;
                side.z = z;
            }
        }
        if (!(side.x == 0 && side.y == 0 && side.z == 0)) {
            VEC_Normalize(&side, &side);
        }
        VEC_MultAdd(0x1800, &side, &toPlayer, &side);
        VEC_Add(func_ov052_020ceb74(enemy), &side, &side);
        if (data_ov058_020d8a40->behaviorFlags & 4) {
            checkStuck = FALSE;
        }
        if (SteerEnemyTowardPoint(enemy, command, &side, checkStuck) || range < distance) {
            if (!(Enemy_GetMoveFlags(data_ov058_020d8a40) & 8)) {
                func_ov058_020d50cc(enemy);
            }
            ai->timer = 0;
        }
        func_ov058_020d4a54(enemy, command);
        UpdateEnemyTargetTracking(enemy, command);
        func_ov058_020d4ffc(enemy, command);
        RefreshAiModeFromFlags(enemy, command);
        break;
    }
    case 2:
        ai->timer += func_ov001_0206db44();
        if (ai->timer > 0xf000) {
            ai->timer = 0;
            ai->mode = 1;
        }
        break;
    case 6: {
        BOOL alone = FALSE;

        if (enemy->partnerSlot == -1) {
            alone = TRUE;
        }
        if (!alone) {
            if (Enemy_CanShareTarget(data_ov058_020d8a40)) {
                enemy->waitTarget = data_ov058_020d8a40->waitTarget;
            }
            command->actions |= 0x400;
        } else {
            ai->flags &= ~0x81000;
            ai->timer = 0;
            ai->retreatTimer = 0xf000;
            ai->mode = 2;
        }
        RefreshAiModeFromFlags(enemy, command);
        break;
    }
    case 5: {
        VecFx32 *waitPos = NULL;
        BOOL arrived = FALSE;

        if (IsWaitTargetReady(&enemy->waitTarget)) {
            waitPos = GetWaitTargetPosition(&enemy->waitTarget);
        }
        if (waitPos != NULL) {
            VecFx32 goal = *waitPos;

            if (HasReachedMoveTarget(enemy, &goal)) {
                if (func_ov058_020d4968(enemy, &goal)) {
                    arrived = TRUE;
                } else {
                    command->actions |= 2;
                }
            } else {
                VecFx32 facing;

                if (IsFacedByPlayer(enemy, &facing)) {
                    VEC_MultAdd(0x900, &facing, &goal, &goal);
                }
                if (SteerEnemyTowardPoint(enemy, command, &goal, FALSE)) {
                    func_ov058_020d50cc(enemy);
                }
            }
            if (arrived) {
                ObjHandle *handle = &enemy->objHandle;
                WaitTarget *wait = &enemy->waitTarget;

                command->arrived = 1;
                command->actions |= 1;
                ai->flags |= 0x1000;
                if (wait->kind == 1 && handle->active != NULL && !IsObjHandleOverLimit(handle)) {
                    StageEventTargetInfo info;
                    BOOL near = FALSE;

                    ai->flags &= ~0x1000;
                    if (GetStageEventTargetInfo(wait->eventId, &info) && info.count > 0 &&
                        VEC_Distance(playerPos, &info.position) < 0xf000) {
                        near = TRUE;
                    }
                    if (!near || (ai->flags & 0x4000)) {
                        ai->retreatTimer = 0xf000;
                        wait->kind = 0;
                    }
                }
            }
        }
        UpdateEnemyTargetTracking(enemy, command);
        RefreshAiModeFromFlags(enemy, command);
        break;
    }
    default:
        func_ov058_020d4a54(enemy, command);
        UpdateEnemyTargetTracking(enemy, command);
        func_ov058_020d4ffc(enemy, command);
        RefreshAiModeFromFlags(enemy, command);
        break;
    }
    return ai->result;
}
