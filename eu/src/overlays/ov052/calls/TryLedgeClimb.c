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
extern s16 data_02053580[];
extern void *GetPlayerControlState(int player);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern BOOL IsStageAllowedForMode(void);
extern void *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_ov021_020a7524(void *unit);
extern u16 func_ov021_020a7564(void *unit);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_NormalizeLength(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                       const VecFx32 *direction, fx32 length, fx32 radius);
extern void InitAxisCylinderShape(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                                           const VecFx32 *axis, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern SweepHit *SweepWorldCollision(CollisionQuery *query);
extern void CheckLinkedTargetClearance(void);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov001_0206e2b0(void);

BOOL TryLedgeClimb(Actor *actor, ClimbState *state)
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
    unit = GetPlayerControlState(actor->player);
    if (actor->player == 0 && data_0205fe0c->noClimb) {
        return climb;
    }
    pos = *func_ov052_020ceb74(actor);
    found = FALSE;
    facing.z = 0;
    facing.y = 0;
    facing.x = 0;
    index = GetLinkedAngleOffset(actor) >> 4;
    facing.x = -data_02053580[index];
    facing.z = -data_02053580[(0x400 - index) & 0xfff];
    secondY = 0x80000000;
    maxY = secondY;
    if (actor->flags & 2) {
        if (state->timer >= 0x5000) {
            contacts = &actor->contacts;
            threshold = 0x650;
            if (IsStageAllowedForMode()) {
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
                    if (ok && VEC_DotProduct(&contacts->normals[i], &facing) < -0xccd) {
                        found = TRUE;
                    }
                    break;
                }
                case 2: {
                    int j;
                    ok = TRUE;
                    for (j = 0; j < 4; j++) {
                        void *mesh = GetWorldMeshNamedEntry(contact->surface->meshIndices[j]);
                        if (mesh != NULL && func_ov001_020681e8(mesh, 2)) {
                            ok = FALSE;
                            break;
                        }
                    }
                    if (ok && VEC_DotProduct(&contacts->normals[i], &facing) < -0xccd) {
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
        } else if (actor->climbMode == 1 && func_ov021_020a7524(unit)) {
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
        VEC_MultAdd(0xc33, &facing, &pos, &start);
        start.y += 0x5000;
        end = start;
        end.y -= 0x19a;
        delta.x = 0;
        delta.y = -0xa000;
        delta.z = 0;
        VEC_Subtract(&end, &start, &diff1);
        axis1 = diff1;
        InitCylinderShape(&shape1, &cylinder, &start, &end, &axis1, VEC_NormalizeLength(&axis1, &axis1), 0x333);
        ledgeSweep.shape = shape1;
        ledgeSweep.delta = delta;
        OffsetBoxByDelta(&ledgeSweep.shape.bounds, &ledgeSweep.sweptBounds, &ledgeSweep.delta);
        sweptCopy = ledgeSweep;
        CollisionQuery_Init(&ledgeQuery, 0, actor->model, 9, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = ledgeQuery;
        modelArg = actor->model;
        callback.func = CheckLinkedTargetClearance;
        callback.arg = &modelArg;
        sweep.callback = callback;
        hit = SweepWorldCollision(&sweep);
        if (hit == NULL) {
            return FALSE;
        }
        if (hit->surface != NULL && hit->blocked == 0) {
            int k;
            for (k = 1; k < 3; k++) {
                void *mesh = GetWorldMeshNamedEntry(hit->surface->meshIndices[k]);
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
        if (IsPlayerEntryFlagSet(0, 0xc) && !func_ov001_0206e2b0()) {
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
        VEC_MultAdd(0xc33, &facing, &start, &end);
        VEC_Subtract(&end, &start, &diff2);
        axis2 = diff2;
        InitAxisCylinderShape(&shape2, &axisStorage, &start, &end, &axis2, VEC_NormalizeLength(&axis2, &axis2));
        shapeCopy = shape2;
        CollisionQuery_Init(&clearanceQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = clearanceQuery;
        if (SweepWorldCollision(&sweep) != NULL) {
            return FALSE;
        }
        if (ledgeTop == (fx32)0x80000000 || !IsStageAllowedForMode()) {
            start = pos;
            VEC_MultAdd(0xdcd, &facing, &start, &end);
            end.y = top - 0x7b;
            VEC_Subtract(&end, &start, &diff3);
            axis3 = diff3;
            InitAxisCylinderShape(&shape3, &axisStorage, &start, &end, &axis3, VEC_NormalizeLength(&axis3, &axis3));
            shapeCopy = shape3;
            CollisionQuery_Init(&lipQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
            sweep = lipQuery;
            if (SweepWorldCollision(&sweep) == NULL) {
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
        VEC_Subtract(&end, &start, &diff4);
        axis4 = diff4;
        InitCylinderShape(&shape4, &cylinder, &start, &end, &axis4, VEC_NormalizeLength(&axis4, &axis4), 0x5cd);
        headSweep.shape = shape4;
        headSweep.delta = delta;
        OffsetBoxByDelta(&headSweep.shape.bounds, &headSweep.sweptBounds, &headSweep.delta);
        sweptCopy = headSweep;
        CollisionQuery_Init(&headQuery, 0, actor->model, 0xe, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = headQuery;
        if (SweepWorldCollision(&sweep) != NULL) {
            ceilingHit = ((CollisionCylinder *)sweptCopy.shape.data)->end;
            if (ceilingHit.y < top) {
                return FALSE;
            }
        }
        height = top - pos.y;
        if (!IsPlayerEntryFlagSet(0, 0xc) || func_ov001_0206e2b0()) {
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
        if (!func_ov021_020a7524(unit)) {
            return FALSE;
        }
        index = func_ov021_020a7564(unit) >> 4;
        facing.x = -data_02053580[index];
        facing.z = -data_02053580[(0x400 - index) & 0xfff];
        start = pos;
        start.y += 0x333;
        VEC_MultAdd(0xd80, &facing, &start, &end);
        VEC_Subtract(&end, &start, &diff5);
        axis5 = diff5;
        InitAxisCylinderShape(&shape5, &axisStorage, &start, &end, &axis5, VEC_NormalizeLength(&axis5, &axis5));
        shapeCopy = shape5;
        CollisionQuery_Init(&stepQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = stepQuery;
        if (SweepWorldCollision(&sweep) != NULL) {
            return FALSE;
        }
        base6 = pos;
        end = base6;
        start = base6;
        end.y += 0x19a;
        delta.x = 0;
        delta.y = 0xa000;
        delta.z = 0;
        VEC_Subtract(&end, &start, &diff6);
        axis6 = diff6;
        InitCylinderShape(&shape6, &cylinder, &start, &end, &axis6, VEC_NormalizeLength(&axis6, &axis6), 0x766);
        stepSweep.shape = shape6;
        stepSweep.delta = delta;
        OffsetBoxByDelta(&stepSweep.shape.bounds, &stepSweep.sweptBounds, &stepSweep.delta);
        sweptCopy = stepSweep;
        CollisionQuery_Init(&stepHeadQuery, 0, actor->model, 0xc, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = stepHeadQuery;
        if (SweepWorldCollision(&sweep) != NULL) {
            ceilingHit = ((CollisionCylinder *)sweptCopy.shape.data)->end;
            if (ceilingHit.y < pos.y + actor->stepHeight + 0xc00) {
                return FALSE;
            }
        }
        VEC_MultAdd(0x4cd, &facing, &pos, &start);
        end = start;
        start.y += 0xc00;
        end.y -= 0xa000;
        VEC_Subtract(&end, &start, &diff7);
        axis7 = diff7;
        InitAxisCylinderShape(&shape7, &axisStorage, &start, &end, &axis7, VEC_NormalizeLength(&axis7, &axis7));
        shapeCopy = shape7;
        CollisionQuery_Init(&floorQuery, 0, actor->model, 9, 1, 0, &shapeCopy, &workspace, NULL);
        sweep = floorQuery;
        if (SweepWorldCollision(&sweep) != NULL) {
            floorHit = ((AxisCylinder *)shapeCopy.data)->top;
            if (floorHit.y > pos.y - 0x800) {
                return FALSE;
            }
        }
        state->speed = 0;
    }
    return TRUE;
}
