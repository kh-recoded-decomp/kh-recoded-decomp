#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int values[2];
} BonusTable;

typedef struct {
    int target;
    int unk_04;
    int current;
    u8 pad_0c[0x12];
    s16 idleTimer;
} Approach;

typedef struct {
    u8 pad_00[0xce];
    s16 motionId;
} MotionInfo;

typedef struct Actor Actor;
typedef void (*StateSetter)(Actor *actor, int state);
typedef void (*TurnCallback)(Actor *actor, u16 angle);
typedef void (*ModeCallback)(Actor *actor, int mode, int arg);
typedef void (*MotionCallback)(Actor *actor, int mode, int arg, int extra);

struct Actor {
    u8 pad_0000[0x1f0];
    MotionCallback onMotion;
    u8 pad_01f4[4];
    ModeCallback onMode;
    u8 pad_01fc[0x210 - 0x1fc];
    TurnCallback onTurn;
    u8 pad_0214[0x230 - 0x214];
    MotionInfo *motion;
    u32 controlFlags;
    u8 pad_0238[0x75c - 0x238];
    int busy;
    u8 pad_0760[8];
    int linked;
    u8 pad_076c[0x9ac - 0x76c];
    u64 flags;
    u8 player;
    u8 pad_09b5[0x9c8 - 0x9b5];
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    fx32 velX;
    fx32 velY;
    fx32 velZ;
    u8 pad_09e0[0x9ec - 0x9e0];
    int frameStep;
    u8 pad_09f0[0xa10 - 0x9f0];
    Approach approach;
    u8 pad_0a30[0xb2c - 0xa30];
    u8 idOwner[0x10ec - 0xb2c];
    StateSetter setState;
};

extern const BonusTable data_ov052_020d20c8;
extern void *func_ov001_0206db78(int player);
extern BOOL func_ov021_020a7504(void *unit);
extern BOOL func_ov052_020c7edc(Actor *actor, Approach *approach);
extern int ApproachTargetValue_020d0e80(Approach *value);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern int GetPlayerEntryCount_02050050(int player, u32 id);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void ApplyTimeScaledSpeed_020c7d28(Actor *actor, fx32 targetSpeed);
extern int ComputeFacingAndDirection_020cebbc(Actor *actor, VecFx32 *out);
extern void ResetIfIdMatches_020a8178(void *owner, int id);

void UpdateGroundMovement_020ca918(Actor *actor)
{
    VecFx32 dir;
    int mode;
    void *unit = func_ov001_0206db78(actor->player);
    u64 flags = actor->flags;
    mode = -1;

    if (flags & 0x400000) {
        actor->setState(actor, 9);
        return;
    }
    if (flags & 0x80) {
        actor->setState(actor, 8);
        return;
    }
    if ((actor->controlFlags & 4) && func_ov052_020c7edc(actor, &actor->approach)) {
        return;
    }
    dir.z = 0;
    dir.y = 0;
    dir.x = 0;
    if (func_ov021_020a7504(unit)) {
        int angle;
        mode = ApproachTargetValue_020d0e80(&actor->approach);
        if (IsPlayerEntryFlagSet_02050014(0, 0x10)) {
            BonusTable table = data_ov052_020d20c8;
            fx32 bonus = table.values[GetPlayerEntryCount_02050050(0, 0x10) - 1];
            mode += FixedPointMultiply12(mode, bonus);
            ApplyTimeScaledSpeed_020c7d28(actor, bonus + 0x1000);
        }
        angle = ComputeFacingAndDirection_020cebbc(actor, &dir);
        dir.x = FixedPointMultiply12(dir.x, mode);
        dir.z = FixedPointMultiply12(dir.z, mode);
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, angle);
        }
        mode = 1;
        actor->posX += dir.x;
        actor->posZ += dir.z;
    } else {
        Approach *approach = &actor->approach;
        approach->current = 0;
        approach->idleTimer += actor->frameStep;
        if (approach->idleTimer >= 0x2000) {
            mode = 0;
            ApplyTimeScaledSpeed_020c7d28(actor, 0x1000);
            if (actor->busy != 0) {
                actor->flags |= 0x2000000;
            }
        }
    }
    if (!(actor->controlFlags & 4)) {
        BOOL moving;
        BOOL horizontal;
        if (actor->posY > 0) {
            actor->flags |= 0x1000;
            actor->setState(actor, 3);
            return;
        }
        moving = TRUE;
        horizontal = TRUE;
        if (actor->velX == 0 && actor->velY == 0) {
            horizontal = FALSE;
        }
        if (!horizontal && actor->velZ == 0) {
            moving = FALSE;
        }
        if (moving) {
            actor->posX += actor->velX;
            actor->posZ += actor->velZ;
            if (actor->posY < 0) {
                actor->setState(actor, 4);
                return;
            }
        } else {
            actor->setState(actor, 4);
            return;
        }
    } else {
        if (mode != -1 && actor->onMode != NULL) {
            actor->onMode(actor, mode, -1);
        }
        if (mode == 1 && actor->linked != 0) {
            ResetIfIdMatches_020a8178(actor->idOwner, 1);
        }
        if ((actor->flags & 0x2000000) && actor->busy == 0 && actor->motion->motionId == -1) {
            if (actor->onMotion != NULL) {
                actor->onMotion(actor, 4, 4, 0);
            }
            actor->flags &= ~0x2000000ULL;
        }
    }
}
