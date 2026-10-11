#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 min;
    VecFx32 max;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 pad_00[0xc];
    u8 flags;
    u8 pad_0d[0x17];
    CollisionShape shape;
    VecFx32 delta;
    Box box;
    u8 pad_68[0x20];
} GroupObject;

typedef struct {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 locked;
    u8 limit;
    u8 counter;
    u8 pad_06[0x2];
    VecFx32 position;
    u8 pad_14[0x4];
    GroupObject *objects;
    s32 mode;
} ObjectGroup;

typedef struct ScrollListener {
    struct ScrollListener *next;
    BOOL (*callback)(u32 arg, const VecFx32 *scroll, s32 state);
    u32 arg;
    s32 state;
    u8 limit;
    u8 count;
} ScrollListener;

typedef struct {
    u8 pad_00[0x1c];
    VecFx32 upVector;
    s32 speed;
    s32 scroll;
    s32 targetSpeed;
    s32 acceleration;
    s32 distance;
    u8 pad_3c[0x1a];
    u8 activeGroupCount;
    u8 pad_57[0xd];
    ObjectGroup *groups;
    u8 pad_68[0x1c];
    s32 slotOffsets[0xe0];
    ScrollListener *listeners;
} OverlayState;

typedef struct {
    u8 pad_00[0xa8];
    VecFx32 position;
} Entity;

typedef struct {
    u32 unk_00;
    int **trees;
} WorldState;

typedef struct {
    u8 pad_00[0x8];
    s32 limit;
} SceneLimit;

extern OverlayState *g_activeState_020bc800;
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern u32 func_ov043_020bc8f8(void);
extern SceneLimit *func_ov043_020bca1c(void);
extern u8 *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Obj_SetPosition_0203569c(Entity *entity, const VecFx32 *position);
extern WorldState *func_02036230(void);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void QuadTree_ReinsertNodeIfFlagSet_02033f10(int *tree, GroupObject *node);
extern void QuadTree_RemoveObject_02033c60(int *tree, GroupObject *node);
extern BOOL func_ov031_020bc650(s32 mode);
extern BOOL AdvanceGroupObjects_020baf38(int index);

static inline void ScaleInto(VecFx32 *out, const VecFx32 *vec, fx32 scale)
{
    *out = *vec;
    ScaleVecFx32InPlace_0204a5e4(out, scale);
}

static inline VecFx32 NegateVec(const VecFx32 *vec)
{
    VecFx32 out = *vec;
    NegateVecFx32_0204aa40(&out);
    return out;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Add_01ff9e0c(a, b, &out);
    return out;
}

static inline void MoveShape(CollisionShape *shape, VecFx32 position)
{
    SetShapePosition_0203afa0(shape, &position);
}

static inline BOOL IsGroupPastLimit(OverlayState *state, ObjectGroup *group)
{
    SceneLimit *limit = func_ov043_020bca1c();

    return group->position.z + state->slotOffsets[group->slot] > limit->limit;
}

void UpdateSceneScroll_020bb054(void)
{
    VecFx32 step;
    VecFx32 move;
    VecFx32 newPosition;
    VecFx32 back;
    VecFx32 scaled;
    Entity *entity;
    WorldState *world;
    int groupCount;
    s32 diff;
    s32 absDiff;
    s32 sign;
    int j;
    int i;
    GroupObject *object;
    ObjectGroup *group;
    OverlayState *state;
    ScrollListener *listener;

    ScaleInto(&scaled, &g_activeState_020bc800->upVector, g_activeState_020bc800->speed);
    move = scaled;
    step = *(const VecFx32 *)&scaled;
    if (func_ov043_020bc8f8() & 8) {
        entity = (Entity *)(GetBoundedEntryField_0206db5c(0) + 0x14);
        back = NegateVec(&move);
        newPosition = AddVec(&entity->position, &back);
        Obj_SetPosition_0203569c(entity, &newPosition);
        return;
    }
    world = func_02036230();
    groupCount = g_activeState_020bc800->activeGroupCount;
    if (g_activeState_020bc800->speed != g_activeState_020bc800->targetSpeed) {
        diff = g_activeState_020bc800->targetSpeed - g_activeState_020bc800->speed;
        absDiff = diff < 0 ? -diff : diff;
        if (absDiff <= g_activeState_020bc800->acceleration) {
            g_activeState_020bc800->speed = g_activeState_020bc800->targetSpeed;
        } else {
            if (diff == 0) {
                sign = 0;
            } else if (diff > 0) {
                sign = 1;
            } else {
                sign = -1;
            }
            g_activeState_020bc800->speed += g_activeState_020bc800->acceleration * sign;
        }
    }
    for (i = 0; i < groupCount; i++) {
        if (g_activeState_020bc800->groups[i].hidden != 0 || i == 0) {
            continue;
        }
        g_activeState_020bc800->groups[i].position = AddVec(&g_activeState_020bc800->groups[i].position, &step);
        for (j = 0; j < g_activeState_020bc800->groups[i].objectCount; j++) {
            object = g_activeState_020bc800->groups[i].objects + j;
            MoveShape(&object->shape, AddVec(object->shape.data, &step));
            OffsetBoxByDelta_0203ac70(&object->shape.bounds, &object->box, &object->delta);
            object->delta = move;
            OffsetBoxByDelta_0203ac70(&object->shape.bounds, &object->box, &object->delta);
            object->flags |= 1;
            QuadTree_ReinsertNodeIfFlagSet_02033f10(*world->trees, object);
        }
        state = *(OverlayState *volatile *)&g_activeState_020bc800;
        group = &g_activeState_020bc800->groups[i];
        if (IsGroupPastLimit(state, group)) {
            if (group->locked != 0 || !func_ov031_020bc650(group->mode) || !AdvanceGroupObjects_020baf38(i)) {
                g_activeState_020bc800->groups[i].hidden = 1;
                for (j = 0; j < g_activeState_020bc800->groups[i].objectCount; j++) {
                    QuadTree_RemoveObject_02033c60(*world->trees, &g_activeState_020bc800->groups[i].objects[j]);
                }
            }
        }
    }
    for (listener = g_activeState_020bc800->listeners; listener != NULL; listener = listener->next) {
        if (listener->callback(listener->arg, &step, listener->state) && listener->limit != 0xff) {
            listener->count++;
            if (listener->count == listener->limit) {
                listener->state = 2;
            }
        }
    }
    g_activeState_020bc800->scroll += g_activeState_020bc800->speed;
    g_activeState_020bc800->distance += g_activeState_020bc800->speed;
}



