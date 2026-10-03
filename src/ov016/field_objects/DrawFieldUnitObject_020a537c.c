#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionBox {
    VecFx32 center;
    VecFx32 halfExtents;
    MtxFx33 axes;
    u8 flags;
} CollisionBox;

typedef struct CollisionShape {
    CollisionBox *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct SceneNode {
    u8 pad_00[0x7c];
    u16 rotation;
    u8 pad_7e[0xa4 - 0x7e];
    VecFx32 position;
    VecFx32 scale;
} SceneNode;

typedef struct FieldActor {
    u32 flags;
    SceneNode node;
    u8 pad_c0[0x130 - 0xc0];
    CollisionShape shape;
} FieldActor;

typedef struct FieldObject {
    u8 pad_00[0x30];
    u16 stateFlags;
    u8 actorId;
    u8 pad_33;
    void *rangeTarget;
    VecFx32 position;
    u8 pad_44[0x3];
    s8 pose;
    u8 pad_48[0x70 - 0x48];
    u16 unk_70_lo : 2;
    u16 flushMode : 1;
    u16 unk_70_mid : 11;
    u16 tall : 1;
    u16 unk_70_hi : 1;
    u8 pad_72[0x77 - 0x72];
    u8 kind;
    u8 pad_78[0x98 - 0x78];
    int depth;
    u8 pad_9c[0xbc - 0x9c];
    u8 unk_bc_lo : 4;
    u8 height : 4;
    u8 unk_bd_lo : 4;
    u8 mode : 4;
    u8 unk_be_lo : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
} FieldObject;

extern const MtxFx33 data_02053444;
extern const s16 data_0205356c[];
extern BOOL func_ov001_020872b8(FieldObject *object);
extern BOOL IsEntityWithinRange_02086cd8(FieldObject *object);
extern FieldActor *func_02036240(int actorId);
extern void func_ov016_020a4438(FieldObject *object, VecFx32 *position);
extern void ApplyFieldObjectBob_020a4950(FieldObject *object, VecFx32 *position, int *depth);
extern BOOL func_ov016_020a41ac(FieldObject *object);
extern BOOL ActorSlot_IsWarmupDoneByIndex_02035d40(int actorId);
extern void ActorSlot_StartWarmupByIndex_02035d80(int actorId);
extern BOOL func_ov021_020af738(CollisionShape *shape, int arg);
extern void PlaceFieldObjectAtPosition_020a2b28(FieldObject *object);
extern void func_ov032_020bf9dc(FieldObject *object, VecFx32 *position);
extern void func_01fff9a0(SceneNode *node, fx32 scale, const MtxFx33 *rotation, int polygonId, int flags);
extern void func_01ff923c(MtxFx33 *mtx, fx32 sin, fx32 cos);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern void TranslateAndFlushGeometry_020864c4(SceneNode *node, int depth, int mode);
extern void func_ov016_020a2bb0(FieldObject *object);

void DrawFieldUnitObject_020a537c(FieldObject *object)
{
    VecFx32 position;
    CollisionShape shape;
    CollisionBox box;
    VecFx32 stacked;
    MtxFx33 rotation;
    int depth;
    FieldActor *actor;
    SceneNode *node;
    BOOL hidden;

    object->flags &= ~0x100000;
    if (func_ov001_020872b8(object) && object->state != 6 && (object->rangeTarget == NULL || IsEntityWithinRange_02086cd8(object)) && !(object->flags & 0x10)) {
        if (object->kind == 0x15) {
            return;
        }
        actor = func_02036240(object->actorId);
        node = &actor->node;
        depth = object->depth;
        object->position = actor->node.position;
        position = object->position;
        switch (object->kind) {
        case 7:
            ApplyFieldObjectBob_020a4950(object, &position, &depth);
            break;
        case 11:
            if (func_ov016_020a41ac(object)) {
                return;
            }
            break;
        case 5:
            func_ov016_020a4438(object, &position);
            break;
        }
        if (!(object->flags & 0x80000) && ActorSlot_IsWarmupDoneByIndex_02035d40(object->actorId)) {
            if (object->depth != 0) {
                int offset;

                shape = actor->shape;
                box = *actor->shape.data;
                shape.data = &box;
                offset = (object->depth - 0x1e0) / 2;
                box.center.y += offset;
                box.halfExtents.y -= offset;
                if (!func_ov021_020af738(&shape, 0)) {
                    return;
                }
            } else if (!func_ov021_020af738(&actor->shape, 0)) {
                return;
            }
            ActorSlot_StartWarmupByIndex_02035d80(object->actorId);
        }
        if (object->flags & 0x40) {
            PlaceFieldObjectAtPosition_020a2b28(object);
        }
        hidden = TRUE;
        if (object->state <= 3 && ((1 << object->state) & 0xb)) {
            hidden = FALSE;
        }
        if (!hidden || (object->flags & 0x20)) {
            node->position = position;
            if (object->mode >= 5) {
                func_ov032_020bf9dc(object, &position);
            } else if (object->tall) {
                int level;

                stacked = position;
                level = object->height - 1;
                stacked.y += level * 0x1800;
                for (; level >= 0; level--, stacked.y -= 0x1800) {
                    node->position = stacked;
                    func_01fff9a0(node, 0x1800, &data_02053444, 0x1f, 1);
                }
            } else if (object->pose != 0 || node->scale.x != 0x1000 || node->scale.y != 0x1000 || node->scale.z != 0x1000) {
                SceneNode_Draw_01ffb12c(node);
            } else {
                if (node->rotation != 0) {
                    int index = node->rotation >> 4;

                    func_01ff923c(&rotation, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
                    func_01fff9a0(node, 0x1800, &rotation, 0x1f, 1);
                } else {
                    func_01fff9a0(node, 0x1800, &data_02053444, 0x1f, 1);
                }
            }
            if ((object->stateFlags & 0x10) && object->depth < 0) {
                TranslateAndFlushGeometry_020864c4(node, depth, object->flushMode);
            }
            node->position = object->position;
        }
        func_ov016_020a2bb0(object);
    }
}
