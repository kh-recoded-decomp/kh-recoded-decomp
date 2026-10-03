#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    VecFx32 direction;
    s32 stats[3];
    s32 pad_24;
    s32 power;
    s32 flags;
    u32 subKind;
    u32 kind;
    s32 count;
    s32 pad_3c;
} ShotDesc;

typedef struct {
    u8 pad_00[4];
    u8 kind;
    u8 subKind;
    u8 pad_06[2];
    s32 power;
} ShotRequest;

typedef struct {
    s32 id;
    s32 kind;
    s32 soundId;
    ShotRequest *request;
    u8 pad_10[0x74];
    void *owner;
} ShotDef;

typedef struct {
    u8 pad_000[0x1078];
    ShotDef *shot;
} ShotActor;

typedef struct {
    u8 pad_00[4];
    VecFx32 offset;
    VecFx32 direction;
    u8 fired : 1;
} ShotAim;

typedef struct {
    s32 stats[3];
    u8 pad_0c[0x16];
    u8 pad_bits : 3;
    u8 mirrored : 1;
    u8 pad_23;
    ShotAim aim;
} ShotPattern;

typedef struct {
    u8 pad_000[0x150];
    ShotDef *shot;
} ShotProjectile;

extern const VecFx32 data_02053438;
extern s32 GetLinkedAngleOffset_020ceb7c(ShotActor *actor);
extern VecFx32 *func_ov052_020ceb54(ShotActor *actor);
extern void ZeroBytes0x40_020ab08c(ShotDesc *desc);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern ShotProjectile *TryConsumeLimitedUse_020ab098(void *owner, ShotDesc *desc);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);

BOOL FireGroupShot_020d8254(ShotActor *actor, void *arg, ShotPattern *pattern)
{
    ShotAim *aim = &pattern->aim;
    int angle;
    ShotDef *shot;
    ShotProjectile *projectile;
    ShotDesc desc;
    VecFx32 direction;

    angle = (u16)(GetLinkedAngleOffset_020ceb7c(actor) + 0x8000);
    shot = actor->shot;
    ZeroBytes0x40_020ab08c(&desc);
    RotateOffsetAroundY_020a9160(&desc.position, func_ov052_020ceb54(actor), angle, &aim->offset);
    RotateOffsetAroundY_020a9160(&direction, &data_02053438, angle, &aim->direction);
    desc.direction = direction;
    func_01ffaff4(&desc.direction, &desc.direction);
    desc.flags = 2;
    if (pattern->mirrored) {
        desc.flags |= 1;
    }
    desc.count = 0;
    desc.stats[0] = pattern->stats[0];
    desc.stats[1] = pattern->stats[1];
    desc.stats[2] = pattern->stats[2];
    desc.pad_3c = 0;
    desc.kind = shot->request->kind;
    desc.subKind = shot->request->subKind;
    desc.power = shot->request->power;
    projectile = TryConsumeLimitedUse_020ab098(shot->owner, &desc);
    if (projectile != NULL) {
        projectile->shot = shot;
        SpawnSoundSlot_0204da8c(shot->soundId, 0, &desc.position, 0);
    }
    aim->fired = TRUE;
    return FALSE;
}
