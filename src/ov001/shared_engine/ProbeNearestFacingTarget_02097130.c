#pragma opt_rotateloops off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitInfo {
    u8 data[0x18];
} HitInfo;

typedef struct TargetObject TargetObject;

typedef struct TargetVtable {
    u8 pad_00[0x24];
    BOOL (*testShape)(TargetObject *obj, void *shape, HitInfo *hit);
} TargetVtable;

struct TargetObject {
    TargetObject *next;
    TargetVtable *vtable;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0x0c];
    u16 flags;
};

typedef struct ProbeInfo {
    u8 pad_00[7];
    u8 mode;
} ProbeInfo;

typedef struct ProbeSource {
    u8 pad_00[0x10];
    void *owner;
    ProbeInfo *info;
    u8 pad_18[4];
    u8 shape[1];
} ProbeSource;

typedef struct PlayerState {
    u8 pad_000[0xac];
    fx32 facingX;
    u8 pad_0b0[4];
    fx32 facingZ;
    u8 pad_0b8[0x208];
    VecFx32 position;
} PlayerState;

typedef struct ContactParams {
    VecFx32 offset;
    u8 alpha;
    u8 kind;
    u8 pad_0e[2];
    fx32 radius;
    s32 unk_14;
    s32 unk_18;
} ContactParams;

typedef struct ProbeResult {
    u32 flags;
    VecFx32 point;
    VecFx32 delta;
    u8 extra[4];
} ProbeResult;

extern int func_ov001_02063a38(void);
extern BOOL Session_Exists_02063a24(void);
extern TargetObject *func_ov001_0208723c(void);
extern int func_ov001_02064794(void);
extern BOOL func_ov016_020a69f0(TargetObject *obj);
extern BOOL func_ov017_020a3d50(TargetObject *obj);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 VEC_Normalize_01ffaff4(VecFx32 *in, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern u32 func_ov001_020863e0(TargetObject *obj, ContactParams *params);
extern const VecFx32 data_02053438;

static inline void VEC_Set(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline int GetSessionMode(void)
{
    if (Session_Exists_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline BOOL IsTargetInView(PlayerState *player, VecFx32 *pos, VecFx32 *delta, VecFx32 *diff, VecFx32 *dir, VecFx32 *facing)
{
    if (GetSessionMode() == 7) {
        return TRUE;
    }
    VEC_Subtract_01ff9e3c(pos, &player->position, diff);
    *delta = *diff;
    diff->y = 0;
    if (VEC_Mag_01ff9f28(diff) < 0x80) {
        return TRUE;
    }
    VEC_Normalize_01ffaff4(diff, dir);
    VEC_Set(facing, player->facingX, 0, player->facingZ);
    VEC_Normalize_01ffaff4(facing, facing);
    if (VEC_DotProduct_01ff9e6c(dir, facing) >= 0x4cd) {
        return TRUE;
    }
    return FALSE;
}

void ProbeNearestFacingTarget_02097130(void *context, PlayerState *player, int unused, void *enabled, ProbeSource *source, ProbeResult *result)
{
    ProbeInfo *info;
    u8 *shape;
    void *owner;
    fx32 bestDist;
    VecFx32 point = {0, 0, 0};
    VecFx32 delta = {0, 0, 0};
    u16 hitFlags = 0;
    TargetObject *best;
    HitInfo hit;
    ContactParams params;
    VecFx32 facing;
    VecFx32 dir;
    VecFx32 diff;
    TargetObject *obj;
    BOOL skip;
    fx32 dist;
    VecFx32 *pos;

    bestDist = 0x64000;
    best = NULL;
    if (context == NULL || player == NULL || func_ov001_02063a38() == 6 || enabled == NULL) {
        return;
    }
    shape = source->shape;
    owner = source->owner;
    info = source->info;
    if (shape == NULL || owner == NULL || info == NULL || info->mode == 0 || owner == NULL) {
        return;
    }
    obj = func_ov001_0208723c();
    while (obj != NULL) {
        skip = FALSE;
        pos = &obj->position;
        switch (func_ov001_02064794()) {
        case 0:
            skip = func_ov016_020a69f0(obj);
            break;
        case 1:
            skip = func_ov017_020a3d50(obj);
            break;
        case 2:
            skip = obj->flags & 8;
            break;
        case 3:
            skip = TRUE;
            break;
        case 4:
            skip = TRUE;
            break;
        }
        if (skip) {
            goto next;
        }
        if (info->mode == 1 && !IsTargetInView(player, pos, &delta, &diff, &dir, &facing)) {
            goto next;
        }
        if (obj->vtable->testShape(obj, shape, &hit)) {
            dist = VEC_Mag_01ff9f28(&delta);
            if (best == NULL || dist < bestDist) {
                best = obj;
                bestDist = dist;
            }
        }
    next:
        obj = obj->next;
    }
    if (best != NULL) {
        params.offset = data_02053438;
        params.alpha = 0xff;
        params.kind = 0;
        params.radius = 0xa000;
        params.unk_14 = 0;
        params.unk_18 = 0;
        if ((u16)func_ov001_020863e0(best, &params) == 1) {
            hitFlags = 2;
        }
    }
    if (hitFlags != 0) {
        result->flags |= hitFlags;
        result->point = point;
        result->delta = delta;
        result->extra[0] = 0;
        result->extra[1] = 0;
        result->extra[2] = 0;
        result->extra[3] = 0;
    }
}
