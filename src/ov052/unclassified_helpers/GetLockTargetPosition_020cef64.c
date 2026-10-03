#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 kind;
    u8 group;
    u8 index;
} TargetInfo;

typedef struct {
    u8 pad0[0x194];
    TargetInfo info;
} TargetOwner;

typedef struct {
    u8 pad0[0x14];
    TargetOwner *owner;
} LockTarget;

typedef struct {
    LockTarget *target;
} LockState;

typedef struct {
    u8 pad0[0x234];
    u32 lockFlags;
    u8 pad238[0xa10 - 0x238];
    LockState lock;
} Actor;

extern u32 func_ov001_0207f038(u32 group, u32 index);
extern int ForwardIfWorkMode12_0207fa14(u32 task, VecFx32 *out, TargetInfo *info);
extern u32 func_ov001_02087224(u32 group, u32 index);
extern unsigned int func_ov001_020863cc(u32 entry, VecFx32 *out);

BOOL GetLockTargetPosition_020cef64(Actor *actor, VecFx32 *out)
{
    BOOL result = FALSE;
    VecFx32 position;
    TargetInfo *info;
    LockState *lock = &actor->lock;
    out->z = 0;
    out->y = 0;
    out->x = 0;
    if (actor->lockFlags & 4) {
        return result;
    }
    if (lock->target == NULL) {
        return result;
    }
    info = &lock->target->owner->info;
    switch (info->kind) {
    case 2:
        if (ForwardIfWorkMode12_0207fa14(func_ov001_0207f038(info->group, info->index), &position, info)) {
            result = TRUE;
        }
        break;
    case 4:
        if (func_ov001_020863cc(func_ov001_02087224(info->group, info->index), &position)) {
            result = TRUE;
        }
        break;
    }
    if (result) {
        *out = position;
    }
    return result;
}
