#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x10];
    u8 collider[0x10c];
    u8 surface[0x1a4];
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 operand[4];
} ScriptCommand;

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
extern const VecFx32 data_ov021_020b5104[8];
extern const VecFx32 data_02053438;

extern s16 *ResolveTaggedValueRef_020b0374(ScriptObject *obj, s16 *value);
extern s32 TaggedValueToFixed_020b03b0(s16 *tagged);
extern fx32 Surface_GetKindValue_02034c24(void *surface);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void func_ov001_02091c34(PlayerActor *actor, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionResult *QueryWorldMotionCollision_02036484(CollisionQuery *query);
extern CollisionResult *ResetAndQueryWorldCollision_0203644c(CollisionQuery *query);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);

s32 ScriptOp_PlaceNearPlayerOnGround_020b1714(ScriptObject *obj, ScriptCommand *cmd)
{
    s16 *distance = ResolveTaggedValueRef_020b0374(obj, cmd->operand);
    PlayerActor *player = data_ov021_020b56a4.player;
    fx32 radius = FixedPointMultiply12(Surface_GetKindValue_02034c24(player->surface), 0xb33);
    int i = 0;
    VecFx32 base;
    VecFx32 start;
    VecFx32 motion;
    CollisionQuery query;

    func_01ff8830(&query, 0, 0x60);
    func_ov001_02091c34(player, &base);
    for (; i < 8; i++) {
        CollisionResult *result;
        start = base;
        start.y += 0x800;
        VEC_MultAdd_01ffa09c(TaggedValueToFixed_020b03b0(distance), &data_ov021_020b5104[i], &data_02053438, &motion);
        func_01ff8830(&query, 0, 0x60);
        query.motion = &motion;
        query.start = &start;
        query.radius = radius;
        query.mask = 0x7f;
        query.ignore = player->collider;
        if (QueryWorldMotionCollision_02036484(&query) == NULL) {
            VEC_MultAdd_01ffa09c(TaggedValueToFixed_020b03b0(distance), &data_ov021_020b5104[i], &base, &start);
            start.y += 0xa000;
            motion.x = 0;
            motion.y = -0x14000;
            motion.z = 0;
            func_01ff8830(&query, 0, 0x60);
            query.motion = &motion;
            query.start = &start;
            query.radius = radius;
            query.mask = 0x7f;
            query.ignore = player->collider;
            result = ResetAndQueryWorldCollision_0203644c(&query);
            if (result != NULL && result->hit != 0) {
                addScaledVector_020301ac(result->fraction, &motion, &start, &obj->position);
                return 0;
            }
        }
    }
    obj->position = player->position;
    return 0;
}
