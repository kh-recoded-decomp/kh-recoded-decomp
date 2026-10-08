#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx.h"

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
    s16 x, y, z;
} VecS16;

typedef struct {
    VecS16 normal;
    u8 pad_06[6];
} EdgeEntry;

typedef struct {
    u8 pad_00[0x12];
    u16 vertexCount;
    VecS16 normal;
    u8 pad_1a[0x20 - 0x1a];
    EdgeEntry edges[4];
    VecFx32 verts[4];
    u8 meshIndices[4];
} WallSurface;

typedef struct {
    u8 type;
    u8 group;
    u8 index;
} ObjectKind;

typedef struct {
    u8 pad_000[0x194];
    ObjectKind kind;
} ObjectInfo;

typedef struct {
    u8 pad_00[0xc];
    u8 flags;
    u8 pad_0d[0x14 - 0xd];
    ObjectInfo *info;
    u8 pad_18[0x40 - 0x18];
    int mode;
    u8 pad_44[0x6c - 0x44];
    int id;
} ContactObject;

typedef struct {
    ContactObject *object;
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
    u32 words[0x18];
} CollisionQuery;

typedef struct {
    int mask;
    int flags;
} QueryFilter;

typedef struct {
    void *mesh;
    WallSurface *surface;
    WallSurface *face;
    u32 pad_0c;
    ContactObject *object;
    u32 words[0x29];
} SweepHit;

typedef struct {
    u8 pad_00[4];
    struct {
        u8 pad_00[0x5a];
        u8 kind;
    } *def;
} StageUnit;

typedef struct {
    VecFx32 target;
    SweepHit hit;
    int timer;
    u16 angle;
    VecFx32 normal;
} ClimbState;

typedef struct {
    u8 pad_00[0xbc];
    fx32 groundY;
    u8 pad_c0[4];
    BOOL grounded;
} MotionInfo;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    StateGetter getState;
    void *model;
    u8 pad_0234[0x274 - 0x234];
    MotionInfo motion;
    u8 pad_033c[0x9ac - 0x33c];
    u64 stateFlags;
    u8 pad_09b4[0x9b8 - 0x9b4];
    int sizeClass;
    u8 pad_09bc[0xa54 - 0x9bc];
    ClimbState climb;
};

extern s16 data_0205356c[];
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *input, VecFx32 *output);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape_0203aeac(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                       const VecFx32 *direction, fx32 length, fx32 radius);
extern void InitAxisCylinderShape_0203adcc(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                                           const VecFx32 *axis, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern SweepHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern BOOL func_02033efc(ContactObject *object);
extern void CopyShortTripleToIntTriple_02033848(void *unused, EdgeEntry *src, VecFx32 *dst);
extern void *GetWorldMeshNamedEntry_0203625c(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);
extern StageUnit *func_ov001_02087224(u32 group, u32 index);
extern int Object_GetKindValue_0208744c(StageUnit *unit);
extern BOOL IsFieldUnitAction5Mode1_020a6ad4(StageUnit *unit);
extern void GetTableValuePair_020a91e8(s32 *outFirst, s32 *outSecond, int index);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern int func_ov001_02063a38(void);
extern BOOL func_ov052_020c9274(Actor *actor, VecFx32 *position);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

BOOL TryGrabLedge_020c8bac(Actor *actor)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape ledgeSweep;
    CollisionQuery ledgeQuery;
    CollisionQuery wallQuery;
    CollisionQuery topQuery;
    CollisionShape shapeCopy;
    AxisCylinder axisStorage;
    CollisionCylinder cylinder;
    VecFx32 base;
    VecFx32 tip;
    VecFx32 delta;
    VecFx32 facing;
    VecFx32 normal;
    VecFx32 wallTop;
    VecFx32 ledgeTop;
    VecFx32 toVert;
    VecFx32 edgeNormal;
    VecFx32 inward;
    VecFx32 point;
    VecFx32 offset;
    MtxFx33 rot;
    VecFx32 axis1;
    VecFx32 diff1;
    CollisionShape shape1;
    CollisionShape shape2;
    VecFx32 diff2;
    VecFx32 axis2;
    CollisionShape shape3;
    VecFx32 diff3;
    VecFx32 axis3;
    VecFx32 wallNormal;
    QueryFilter filter;
    s32 lift;
    s32 reach;
    QueryFilter filterInit;
    VecFx32 *pos;
    ClimbState *climb;
    MotionInfo *motion;
    int i;
    int type;
    ContactObject *object;
    SweepHit *hit;
    int index;
    fx32 y;
    BOOL blocked;

    pos = func_ov052_020ceb54(actor);
    climb = &actor->climb;
    if (actor->stateFlags & 0x8000000) {
        return FALSE;
    }
    if (climb->timer > 0) {
        return FALSE;
    }
    if (GetActorState(actor) == 4 || GetActorState(actor) == 2) {
        return FALSE;
    }
    facing.z = 0;
    facing.y = 0;
    facing.x = 0;
    index = GetLinkedAngleOffset_020ceb7c(actor) >> 4;
    facing.x = -data_0205356c[index];
    facing.z = -data_0205356c[(0x400 - index) & 0xfff];
    filterInit.mask = 0;
    filterInit.flags = 0x20;
    filter = filterInit;
    motion = &actor->motion;
    if (motion->grounded && func_ov052_020ceb54(actor)->y - motion->groundY < 0xe00) {
        return FALSE;
    }

    tip = *pos;
    base = tip;
    tip.y += 0x19a;
    delta.x = 0;
    delta.y = 0xa000;
    delta.z = 0;
    VEC_Subtract_01ff9e3c(&tip, &base, &diff1);
    axis1 = diff1;
    InitCylinderShape_0203aeac(&shape1, &cylinder, &base, &tip, &axis1, func_01ffaff4(&axis1, &axis1), 0x900);
    ledgeSweep.shape = shape1;
    ledgeSweep.delta = delta;
    OffsetBoxByDelta_0203ac70(&ledgeSweep.shape.bounds, &ledgeSweep.sweptBounds, &ledgeSweep.delta);
    sweptCopy = ledgeSweep;
    CollisionQuery_Init_02034c74(&ledgeQuery, 0, actor->model, 4, 1, 1, &sweptCopy, &workspace, &filter);
    sweep = ledgeQuery;
    if (SweepWorldCollision_020364a0(&sweep) != NULL &&
        ((CollisionCylinder *)sweptCopy.shape.data)->end.y < pos->y + 0x2000) {
        return FALSE;
    }

    tip = *pos;
    base = tip;
    y = pos->y + 0x800;
    tip.y = y;
    base.y = y;
    VEC_MultAdd_01ffa09c(0xb00, &facing, &tip, &tip);
    VEC_Subtract_01ff9e3c(&tip, &base, &diff2);
    axis2 = diff2;
    InitAxisCylinderShape_0203adcc(&shape2, &axisStorage, &base, &tip, &axis2, func_01ffaff4(&axis2, &axis2));
    shapeCopy = shape2;
    CollisionQuery_Init_02034c74(&wallQuery, 0, actor->model, 10, 1, 0, &shapeCopy, &workspace, &filter);
    sweep = wallQuery;
    hit = SweepWorldCollision_020364a0(&sweep);
    if (hit == NULL) {
        return FALSE;
    }
    object = hit->object;
    if (object != NULL) {
        type = object->info->kind.type;
        blocked = FALSE;
        switch (type) {
        case 1:
            if (object->id != 0x1a) {
                blocked = TRUE;
            } else if (object->flags & 1) {
                blocked = TRUE;
            }
            break;
        case 2:
        case 4:
            break;
        default:
            blocked = TRUE;
            break;
        }
        if (blocked) {
            return FALSE;
        }
        if (func_02033efc(object)) {
            return FALSE;
        }
    }
    if (VEC_DotProduct_01ff9e6c(&workspace.normals[0], &facing) > -0x333) {
        return FALSE;
    }
    normal = workspace.normals[0];
    if (hit->face != NULL && hit->object == NULL) {
        i = 0;
        if ((int)hit->face->vertexCount > 0) {
            do {
                CopyShortTripleToIntTriple_02033848(hit->mesh, &hit->face->edges[i], &edgeNormal);
                if (edgeNormal.y <= 0xb33 && edgeNormal.y >= -0xb33) {
                    VEC_Subtract_01ff9e3c(&base, &hit->face->verts[i], &toVert);
                    if (VEC_DotProduct_01ff9e6c(&edgeNormal, &toVert) >= 0) {
                        return FALSE;
                    }
                }
            } while (++i < hit->face->vertexCount);
        }
    }
    wallTop = ((AxisCylinder *)shapeCopy.data)->top;
    climb->hit = *hit;

    inward.x = -normal.x;
    inward.z = -normal.z;
    inward.y = 0;
    VEC_NormalizeUnchecked_01ff9f88(&inward, &inward);
    VEC_MultAdd_01ffa09c(0x333, &inward, &wallTop, &base);
    base.y += 0x1ccd;
    tip = base;
    tip.y -= 0x8000;
    VEC_Subtract_01ff9e3c(&tip, &base, &diff3);
    axis3 = diff3;
    InitAxisCylinderShape_0203adcc(&shape3, &axisStorage, &base, &tip, &axis3, func_01ffaff4(&axis3, &axis3));
    shapeCopy = shape3;
    CollisionQuery_Init_02034c74(&topQuery, 0, actor->model, 9, 1, 0, &shapeCopy, &workspace, &filter);
    sweep = topQuery;
    hit = SweepWorldCollision_020364a0(&sweep);
    if (hit == NULL) {
        return FALSE;
    }
    if (hit->surface != NULL && hit->object == NULL) {
        int k;
        k = 1;
        do {
            void *mesh = GetWorldMeshNamedEntry_0203625c(hit->surface->meshIndices[k]);
            if (mesh != NULL && (func_ov001_020681e8(mesh, 3) || func_ov001_020681e8(mesh, 5))) {
                return FALSE;
            }
        } while (++k < 3);
        {
            VecS16 *surfaceNormal = &hit->surface->normal;
            wallNormal.x = surfaceNormal->x;
            wallNormal.y = surfaceNormal->y;
            wallNormal.z = surfaceNormal->z;
            climb->normal = wallNormal;
        }
    }
    i = 0;
    if ((int)workspace.count > 0) {
        do {
        ContactHit *contact = &workspace.hits[i];
        if (contact->kind == 4) {
            ContactObject *object = contact->object;
            ObjectKind *kind = &object->info->kind;
            BOOL ok = FALSE;
            switch (kind->type) {
            case 2:
                ok = TRUE;
                if (object->mode == 0 || object->mode == 3) {
                    ok = FALSE;
                }
                break;
            case 4: {
                StageUnit *unit = func_ov001_02087224(kind->group, kind->index);
                ok = TRUE;
                if (unit->def->kind == 4 || unit->def->kind == 9) {
                    switch (Object_GetKindValue_0208744c(unit)) {
                    case 3:
                    case 7:
                        ok = FALSE;
                        break;
                    case 5:
                        if (IsFieldUnitAction5Mode1_020a6ad4(unit)) {
                            ok = TRUE;
                        }
                        break;
                    }
                }
                break;
            }
            case 1:
                if (object->id == 0x1a && !(hit->object->flags & 2)) {
                    ok = TRUE;
                }
                break;
            }
            if (!ok) {
                return FALSE;
            }
            climb->normal = workspace.normals[i];
        }
        } while (++i < workspace.count);
    }
    ledgeTop = ((AxisCylinder *)shapeCopy.data)->top;
    y = ledgeTop.y;
    if (pos->y + 0x1800 < y) {
        return FALSE;
    }
    if (pos->y > y) {
        return FALSE;
    }
    GetTableValuePair_020a91e8(&lift, &reach, actor->sizeClass);
    point = wallTop;
    point.y = y - lift;
    VEC_MultAdd_01ffa09c(0x780, &normal, &point, &point);
    climb->angle = FixedPointAtan2_020062bc(normal.x, normal.z);
    index = climb->angle >> 4;
    MTX_RotY33_01ff923c(&rot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    offset.x = reach;
    offset.y = 0;
    offset.z = 0;
    MTX_MultVec33_01ff9404(&offset, &rot, &offset);
    VEC_Add_01ff9e0c(&point, &offset, &climb->target);
    if (func_ov001_02063a38() == 4) {
        climb->target.z = 0;
    }
    if (!func_ov052_020c9274(actor, &climb->target)) {
        return FALSE;
    }
    return TRUE;
}
