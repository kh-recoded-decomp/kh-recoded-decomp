#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct {
    VecFx32 base;
    VecFx32 top;
    VecFx32 axis;
    fx32 radius;
} AxisCylinder;

typedef struct {
    u8 pad_00[0x12];
    u16 vertexCount;
    s16 normalX;
    s16 normalY;
    s16 normalZ;
    u8 pad_1a[0x50 - 0x1a];
    VecFx32 verts[4];
    u8 meshIndices[4];
} WallSurface;

typedef struct {
    u8 pad_000[0x194];
    u8 type;
} ObjectInfo;

typedef struct {
    u8 pad_00[0x14];
    ObjectInfo *info;
    u8 pad_18[0x6c - 0x18];
    int id;
} ContactObject;

typedef struct {
    WallSurface *surface;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
    u8 pad_181[0x1a4 - 0x181];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x14];
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 pad_00[4];
    WallSurface *surface;
    u8 pad_08[8];
    int blocked;
} SweepHit;

typedef struct {
    u8 pad_000[0x230];
    void *model;
    u32 flags;
    u8 pad_238[0x344 - 0x238];
    QueryWorkspace contacts;
    u8 pad_4e8[0x9b4 - 0x4e8];
    u8 player;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int climbMode;
    u8 pad_9c4[0xa0c - 0x9c4];
    fx32 stepHeight;
} Actor;

typedef struct {
    u8 pad_00[0x28];
    fx32 speed;
    int timer;
} ClimbState;

typedef struct {
    u8 pad_0000[0x2878];
    u32 pad_bits : 17;
    u32 noClimb : 1;
} GameFlags;

extern GameFlags *data_0205fe0c;
extern s16 data_0205356c[];
extern void *func_ov001_0206db78(int player);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern BOOL IsStageAllowedForMode_020c8008(void);
extern void *GetWorldMeshNamedEntry_0203625c(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_ov021_020a7504(void *unit);
extern u16 func_ov021_020a7544(void *unit);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape_0203aeac(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                       const VecFx32 *direction, fx32 length, fx32 radius);
extern void InitAxisCylinderShape_0203adcc(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                                           const VecFx32 *axis, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern SweepHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov021_020a9308(void);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern BOOL func_ov001_0206e2b0(void);

BOOL TryLedgeClimb_020cefe8(Actor *actor, ClimbState *state)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape ledgeSweep;
    CollisionQuery ledgeQuery;
    CollisionQuery clearanceQuery;
    CollisionQuery lipQuery;
    SweptShape headSweep;
    CollisionQuery headQuery;
    CollisionQuery stepQuery;
    SweptShape stepSweep;
    CollisionQuery stepHeadQuery;
    CollisionQuery floorQuery;
    CollisionShape shapeCopy;
    AxisCylinder axisStorage;
    CollisionCylinder cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 delta;
    VecFx32 ledgeHit;
    VecFx32 ceilingHit;
    VecFx32 pos;
    VecFx32 facing;
    VecFx32 normal;
    VecFx32 floorHit;
    VecFx32 surfaceNormal;
    VecFx32 axis1;
    VecFx32 diff1;
    CollisionShape shape1;
    CollisionShape shape2;
    VecFx32 diff2;
    VecFx32 axis2;
    CollisionShape shape3;
    VecFx32 diff3;
    VecFx32 axis3;
    VecFx32 axis4;
    VecFx32 diff4;
    CollisionShape shape4;
    CollisionShape shape5;
    VecFx32 diff5;
    VecFx32 axis5;
    VecFx32 axis6;
    VecFx32 diff6;
    CollisionShape shape6;
    CollisionShape shape7;
    VecFx32 diff7;
    VecFx32 axis7;
    VecFx32 base4;
    VecFx32 base6;
    void *modelArg;
    QueryCallback callback;
    fx32 ledgeTop;
    int i;
    BOOL climb;
    BOOL boosted;
    BOOL special;
    void *unit;
    QueryWorkspace *contacts;
    BOOL found;
    fx32 threshold;
    fx32 maxY;
    fx32 secondY;
    int index;
    SweepHit *hit;
    fx32 top;

    ledgeTop = 0x80000000;
    climb = FALSE;
    boosted = FALSE;
    special = FALSE;
    unit = func_ov001_0206db78(actor->player);
    if (actor->player == 0 && data_0205fe0c->noClimb) {
        return climb;
    }
    pos = *func_ov052_020ceb54(actor);
    found = FALSE;
    facing.z = 0;
    facing.y = 0;
    facing.x = 0;
    index = GetLinkedAngleOffset_020ceb7c(actor) >> 4;
    facing.x = -data_0205356c[index];
    facing.z = -data_0205356c[(0x400 - index) & 0xfff];
    secondY = 0x80000000;
    maxY = secondY;
    if (actor->flags & 2) {
        if (state->timer >= 0x5000) {
            contacts = &actor->contacts;
            threshold = 0x650;
            if (IsStageAllowedForMode_020c8008()) {
                threshold = 0x7f0;
            }
            for (i = 0; i < contacts->count && !found; i++) {
                ContactHit *contact = &contacts->hits[i];
                BOOL ok = FALSE;
                switch (contact->kind) {
                case 4: {
                    ContactObject *object = (ContactObject *)contact->surface;
                    u8 type = object->info->type;
                    if (type == 4) {
                        ok = TRUE;
                    }
                    if (type == 1) {
                        switch (object->id) {
                        case 0x19:
                            special = TRUE;
                        case 0x1a:
                            ok = TRUE;
                            break;
                        }
                    }
                    if (ok && VEC_DotProduct_01ff9e6c(&contacts->normals[i], &facing) < -0xccd) {
                        found = TRUE;
                    }
                    break;
                }
                case 2: {
                    int j;
                    ok = TRUE;
                    for (j = 0; j < 4; j++) {
                        void *mesh = GetWorldMeshNamedEntry_0203625c(contact->surface->meshIndices[j]);
                        if (mesh != NULL && func_ov001_020681e8(mesh, 2)) {
                            ok = FALSE;
                            break;
                        }
                    }
                    if (ok && VEC_DotProduct_01ff9e6c(&contacts->normals[i], &facing) < -0xccd) {
                        WallSurface *surface = contact->surface;
                        surfaceNormal.x = surface->normalX;
                        surfaceNormal.y = surface->normalY;
                        surfaceNormal.z = surface->normalZ;
                        normal = surfaceNormal;
                        if (normal.y < threshold && surface->vertexCount == 4) {
                            for (j = 0; j < 4; j++) {
                                fx32 y = surface->verts[j].y;
                                if (y > maxY) {
                                    if (maxY > secondY) {
                                        secondY = maxY;
                                    }
                                    maxY = y;
                                } else if (y > secondY) {
                                    secondY = y;
                                }
                            }
                            if (normal.y != 0) {
                                ledgeTop = maxY;
                            }
                            found = TRUE;
                        }
                    }
                    break;
                }
                }
            }
            if (found) {
                climb = TRUE;
            }
        } else if (actor->climbMode == 1 && func_ov021_020a7504(unit)) {
            state->timer += 0x1000;
            boosted = TRUE;
        }
    }
    if (!boosted) {
        state->timer = 0;
    }
    if (climb) {
        fx32 maxRise;
        fx32 specialRise;
        fx32 height;
        VEC_MultAdd_01ffa09c(0xc33, &facing, &pos, &start);
        start.y += 0x5000;
        end = start;
        end.y -= 0x19a;
        delta.x = 0;
        delta.y = -0xa000;
        delta.z = 0;
        VEC_Subtract_01ff9e3c(&end, &start, &diff1);
        axis1 = diff1;
        InitCylinderShape_0203aeac(&shape1, &cylinder, &start, &end, &axis1, func_01ffaff4(&axis1, &axis1), 0x333);
        ledgeSweep.shape = shape1;
        ledgeSweep.delta = delta;
        OffsetBoxByDelta_0203ac70(&ledgeSweep.shape.bounds, &ledgeSweep.sweptBounds, &ledgeSweep.delta);
        sweptCopy = ledgeSweep;
        CollisionQuery_Init_02034c74(&ledgeQuery, 0, actor->model, 9, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = ledgeQuery;
        modelArg = actor->model;
        callback.func = func_ov021_020a9308;
        callback.arg = &modelArg;
        sweep.callback = callback;
        hit = SweepWorldCollision_020364a0(&sweep);
        if (hit == NULL) {
            return FALSE;
        }
        if (hit->surface != NULL && hit->blocked == 0) {
            int k;
            for (k = 1; k < 3; k++) {
                void *mesh = GetWorldMeshNamedEntry_0203625c(hit->surface->meshIndices[k]);
                if (mesh != NULL && (func_ov001_020681e8(mesh, 3) || func_ov001_020681e8(mesh, 5))) {
                    special = TRUE;
                    break;
                }
            }
        }
        ledgeHit = ((CollisionCylinder *)sweptCopy.shape.data)->end;
        top = ledgeHit.y;
        if (ledgeTop != (fx32)0x80000000 && top < ledgeTop) {
            top = ledgeTop;
        }
        maxRise = 0x3800;
        specialRise = 0x2666;
        if (IsPlayerEntryFlagSet_02050014(0, 0xc) && !func_ov001_0206e2b0()) {
            specialRise = 0x3e66;
            maxRise = 0x5000;
        }
        if (top > pos.y + maxRise) {
            return FALSE;
        }
        if (special && top > pos.y + specialRise) {
            return FALSE;
        }
        start = pos;
        start.y = top + 0x19a;
        VEC_MultAdd_01ffa09c(0xc33, &facing, &start, &end);
        VEC_Subtract_01ff9e3c(&end, &start, &diff2);
        axis2 = diff2;
        InitAxisCylinderShape_0203adcc(&shape2, &axisStorage, &start, &end, &axis2, func_01ffaff4(&axis2, &axis2));
        shapeCopy = shape2;
        CollisionQuery_Init_02034c74(&clearanceQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = clearanceQuery;
        if (SweepWorldCollision_020364a0(&sweep) != NULL) {
            return FALSE;
        }
        if (ledgeTop == (fx32)0x80000000 || !IsStageAllowedForMode_020c8008()) {
            start = pos;
            VEC_MultAdd_01ffa09c(0xdcd, &facing, &start, &end);
            end.y = top - 0x7b;
            VEC_Subtract_01ff9e3c(&end, &start, &diff3);
            axis3 = diff3;
            InitAxisCylinderShape_0203adcc(&shape3, &axisStorage, &start, &end, &axis3, func_01ffaff4(&axis3, &axis3));
            shapeCopy = shape3;
            CollisionQuery_Init_02034c74(&lipQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
            sweep = lipQuery;
            if (SweepWorldCollision_020364a0(&sweep) == NULL) {
                return FALSE;
            }
        }
        base4 = pos;
        end = base4;
        start = base4;
        end.y += 0x19a;
        delta.x = 0;
        delta.y = 0xa000;
        delta.z = 0;
        VEC_Subtract_01ff9e3c(&end, &start, &diff4);
        axis4 = diff4;
        InitCylinderShape_0203aeac(&shape4, &cylinder, &start, &end, &axis4, func_01ffaff4(&axis4, &axis4), 0x5cd);
        headSweep.shape = shape4;
        headSweep.delta = delta;
        OffsetBoxByDelta_0203ac70(&headSweep.shape.bounds, &headSweep.sweptBounds, &headSweep.delta);
        sweptCopy = headSweep;
        CollisionQuery_Init_02034c74(&headQuery, 0, actor->model, 0xe, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = headQuery;
        if (SweepWorldCollision_020364a0(&sweep) != NULL) {
            ceilingHit = ((CollisionCylinder *)sweptCopy.shape.data)->end;
            if (ceilingHit.y < top) {
                return FALSE;
            }
        }
        height = top - pos.y;
        if (!IsPlayerEntryFlagSet_02050014(0, 0xc) || func_ov001_0206e2b0()) {
            if (height <= 0x14cd) {
                state->speed = 0x3000;
            } else if (height <= 0x1b33) {
                state->speed = 0x5000;
            } else if (height <= 0x24cd) {
                state->speed = 0x8000;
            } else {
                state->speed = 0;
            }
        } else if (height <= 0x1000) {
            state->speed = 0x1000;
        } else if (height <= 0x14cd) {
            state->speed = 0x2000;
        } else if (height <= 0x1ccd) {
            state->speed = 0x3000;
        } else if (height <= 0x219a) {
            state->speed = 0x4000;
        } else if (height <= 0x2666) {
            state->speed = 0x5000;
        } else if (height <= 0x299a) {
            state->speed = 0x6000;
        } else if (height <= 0x2ccd) {
            state->speed = 0x7000;
        } else if (height <= 0x2e66) {
            state->speed = 0x8000;
        } else if (height <= 0x3000) {
            state->speed = 0x9000;
        } else if (height <= 0x3333) {
            state->speed = 0xa000;
        } else if (height <= 0x3666) {
            state->speed = 0xb000;
        } else {
            state->speed = 0;
        }
    } else {
        if (!func_ov021_020a7504(unit)) {
            return FALSE;
        }
        index = func_ov021_020a7544(unit) >> 4;
        facing.x = -data_0205356c[index];
        facing.z = -data_0205356c[(0x400 - index) & 0xfff];
        start = pos;
        start.y += 0x333;
        VEC_MultAdd_01ffa09c(0xd80, &facing, &start, &end);
        VEC_Subtract_01ff9e3c(&end, &start, &diff5);
        axis5 = diff5;
        InitAxisCylinderShape_0203adcc(&shape5, &axisStorage, &start, &end, &axis5, func_01ffaff4(&axis5, &axis5));
        shapeCopy = shape5;
        CollisionQuery_Init_02034c74(&stepQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = stepQuery;
        if (SweepWorldCollision_020364a0(&sweep) != NULL) {
            return FALSE;
        }
        base6 = pos;
        end = base6;
        start = base6;
        end.y += 0x19a;
        delta.x = 0;
        delta.y = 0xa000;
        delta.z = 0;
        VEC_Subtract_01ff9e3c(&end, &start, &diff6);
        axis6 = diff6;
        InitCylinderShape_0203aeac(&shape6, &cylinder, &start, &end, &axis6, func_01ffaff4(&axis6, &axis6), 0x766);
        stepSweep.shape = shape6;
        stepSweep.delta = delta;
        OffsetBoxByDelta_0203ac70(&stepSweep.shape.bounds, &stepSweep.sweptBounds, &stepSweep.delta);
        sweptCopy = stepSweep;
        CollisionQuery_Init_02034c74(&stepHeadQuery, 0, actor->model, 0xc, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = stepHeadQuery;
        if (SweepWorldCollision_020364a0(&sweep) != NULL) {
            ceilingHit = ((CollisionCylinder *)sweptCopy.shape.data)->end;
            if (ceilingHit.y < pos.y + actor->stepHeight + 0xc00) {
                return FALSE;
            }
        }
        VEC_MultAdd_01ffa09c(0x4cd, &facing, &pos, &start);
        end = start;
        start.y += 0xc00;
        end.y -= 0xa000;
        VEC_Subtract_01ff9e3c(&end, &start, &diff7);
        axis7 = diff7;
        InitAxisCylinderShape_0203adcc(&shape7, &axisStorage, &start, &end, &axis7, func_01ffaff4(&axis7, &axis7));
        shapeCopy = shape7;
        CollisionQuery_Init_02034c74(&floorQuery, 0, actor->model, 9, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = floorQuery;
        if (SweepWorldCollision_020364a0(&sweep) != NULL) {
            floorHit = ((AxisCylinder *)shapeCopy.data)->top;
            if (floorHit.y > pos.y - 0x800) {
                return FALSE;
            }
        }
        state->speed = 0;
    }
    return TRUE;
}
