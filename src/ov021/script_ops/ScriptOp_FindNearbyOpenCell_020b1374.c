#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 collider[0x10c];
    u8 surface[0x1a4];
} ActorBody;

typedef struct {
    u8 pad_00[0x10];
    ActorBody body;
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x2c];
    u16 hasResult;
    u16 pad_2e;
    s32 result;
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 operand[4];
} ScriptCommand;

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
    u8 data[0x10];
} ShapeStorage;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 data[0x18];
} SweepQuery;

typedef struct {
    VecFx32 *start;
    VecFx32 *motion;
    fx32 radius;
    u16 pad_0c;
    u16 mask;
    void *ignore;
    u8 pad_14[0x4c];
} CollisionQuery;

typedef struct {
    u32 pad_00;
    u32 hit;
    u8 pad_08[0x24];
    fx32 fraction;
} CollisionResult;

extern FieldContext data_ov021_020b56a4;
extern const VecFx32 data_ov021_020b5164[8];
extern const VecFx32 data_02053438;

extern s16 *ResolveTaggedValueRef_020b0374(ScriptObject *obj, s16 *value);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern fx32 Surface_GetKindValue_02034c24(void *surface);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_ov001_02091c34(PlayerActor *actor, VecFx32 *out);
extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionShape func_0203ad14(ShapeStorage *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweptShape *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(SweepQuery *query);
extern CollisionResult *ResetAndQueryWorldCollision_0203644c(CollisionQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

s32 ScriptOp_FindNearbyOpenCell_020b1374(ScriptObject *obj, ScriptCommand *cmd)
{
    SweepQuery sweep;
    CollisionQuery query;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape swept;
    SweepQuery initQuery;
    VecFx32 playerPos;
    VecFx32 cell;
    VecFx32 hitPos;
    VecFx32 start;
    VecFx32 motion;
    VecFx32 diff;
    ShapeStorage storage;
    VecFx32 zero;
    s32 filter[2];
    PlayerActor *player;
    ActorBody *body;
    fx32 best;
    fx32 radius;
    fx32 halfRadius;
    s32 i;

    ResolveTaggedValueRef_020b0374(obj, cmd->operand);
    player = data_ov021_020b56a4.player;
    body = &player->body;
    obj->hasResult = 1;
    obj->result = 0;
    obj->position = player->position;
    func_01ff8830(&query, 0, 0x60);
    radius = FixedPointMultiply12(Surface_GetKindValue_02034c24(body->surface), 0x1000);
    playerPos = player->position;
    func_ov001_02091c34(player, &cell);
    if (cell.x < 0) {
        cell.x = func_02023dbc(cell.x, 0x3000) * 0x3000 - 0x1800;
    } else {
        cell.x = func_02023dbc(cell.x, 0x3000) * 0x3000 + 0x1800;
    }
    if (cell.z < 0) {
        cell.z = func_02023dbc(cell.z, 0x3000) * 0x3000 - 0x1800;
    } else {
        cell.z = func_02023dbc(cell.z, 0x3000) * 0x3000 + 0x1800;
    }
    best = 0x7fffffff;
    zero = data_02053438;
    halfRadius = radius >> 1;
    for (i = 0; i < 8; i++) {
        start = cell;
        start.y += 0x800;
        VEC_MultAdd_01ffa09c(0x3000, &data_ov021_020b5164[i], &start, &start);
        swept.shape = func_0203ad14(&storage, &start, radius);
        swept.delta = zero;
        OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        CollisionQuery_Init_02034c74(&initQuery, 0x70, body, 10, 1, 1, &sweptCopy, &workspace, filter);
        sweep = initQuery;
        if (SweepWorldCollision_020364a0(&sweep) == NULL) {
            CollisionResult *result;

            VEC_MultAdd_01ffa09c(0x3000, &data_ov021_020b5164[i], &cell, &start);
            start.y += 0xa000;
            motion.x = 0;
            motion.y = -0x14000;
            motion.z = 0;
            func_01ff8830(&query, 0, 0x60);
            query.motion = &motion;
            query.start = &start;
            query.radius = halfRadius;
            query.mask = 0x70;
            query.ignore = &player->body;
            result = ResetAndQueryWorldCollision_0203644c(&query);
            if (result != NULL && result->hit != 0) {
                fx32 distance;

                addScaledVector_020301ac(result->fraction, &motion, &start, &hitPos);
                VEC_Subtract_01ff9e3c(&hitPos, &playerPos, &diff);
                if (VEC_Mag_01ff9f28(&diff) >= 0xc00) {
                    VEC_Subtract_01ff9e3c(&hitPos, &cell, &diff);
                    distance = VEC_Mag_01ff9f28(&diff);
                    if (distance <= 0x6000 && distance < best) {
                        best = distance;
                        obj->position = hitPos;
                        obj->result = 1;
                    }
                }
            }
        }
    }
    return 0;
}
