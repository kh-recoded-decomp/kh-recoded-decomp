#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Enemy Enemy;
typedef u32 (*EnemyFlagGetter)(Enemy *enemy);

typedef struct {
    u8 pad_00[0x14];
    s32 stuckTimer;
    u8 pad_18[0x10];
    u16 moveAngle;
    u8 pad_2a[6];
    VecFx32 lastPos;
} AiState;

typedef struct {
    u8 pad_00[0xe];
    u16 flags;
} MoveRequest;

struct Enemy {
    u8 pad_000[0x21c];
    EnemyFlagGetter getMoveFlags;
    u8 pad_220[0x4e5 - 0x220];
    u8 alwaysAlert;
    u8 pad_4e6[0x9ac - 0x4e6];
    u64 stateFlags;
    u8 pad_9b4[0x1258 - 0x9b4];
    AiState ai;
};

extern VecFx32 *func_ov052_020ceb54(Enemy *enemy);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern u16 FixedPointAtan2_020062bc(fx32 x, fx32 z);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_ov001_0206db44(void);

BOOL SteerEnemyTowardPoint_020d4524(Enemy *enemy, MoveRequest *request, const VecFx32 *dest)
{
    AiState *ai = &enemy->ai;
    VecFx32 *pos = func_ov052_020ceb54(enemy);
    fx32 limit = 0x3c000;
    BOOL result = FALSE;
    BOOL checkStuck = TRUE;
    VecFx32 dir;
    VecFx32 current;
    VecFx32 last;
    fx32 dy;
    fx32 dist;
    u32 moveFlags;

    VEC_Subtract_01ff9e3c(dest, pos, &dir);
    dy = dir.y;
    dir.y = 0;
    dist = VEC_Mag_01ff9f28(&dir);
    if (dist != 0) {
        func_01ff9f88(&dir, &dir);
    } else {
        return result;
    }
    ai->moveAngle = FixedPointAtan2_020062bc(dir.x, dir.z) + 0x8000;
    request->flags |= 0x40;
    if (enemy->alwaysAlert) {
        limit = 0x5000;
    }
    if (dist < 0x2000) {
        if (enemy->getMoveFlags != NULL) {
            moveFlags = enemy->getMoveFlags(enemy);
        } else {
            moveFlags = 0;
        }
        if ((moveFlags & 8) == 0 && (enemy->stateFlags & 0x10000) == 0) {
            request->flags &= ~0x40;
        }
        if ((dy < 0 ? -dy : dy) < 0x4000) {
            checkStuck = FALSE;
        }
    }
    current = *pos;
    last = ai->lastPos;
    last.y = 0;
    current.y = 0;
    if (checkStuck) {
        if (dy < 0) {
            dy = -dy;
        }
        if (dy > 0x4000 || func_01ffa0f4(&current, &last) < 0x1000) {
            ai->stuckTimer += func_ov001_0206db44();
            if (limit < ai->stuckTimer) {
                ai->stuckTimer = 0;
                result = TRUE;
            }
            goto done;
        }
    }
    ai->lastPos = *func_ov052_020ceb54(enemy);
    ai->stuckTimer = 0;
done:
    return result;
}
