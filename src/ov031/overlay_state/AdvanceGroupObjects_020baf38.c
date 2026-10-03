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
    u8 pad_00[0x24];
    CollisionShape shape;
    VecFx32 delta;
    Box box;
    u8 pad_68[0x20];
} GroupObject;

typedef struct {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 pad_03;
    u8 limit;
    u8 counter;
    u8 pad_06[0x2];
    VecFx32 position;
    u8 pad_14[0x4];
    GroupObject *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x64];
    ObjectGroup *groups;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern fx32 GetNegatedCombinedOffset_020bc68c(int offset);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
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

BOOL AdvanceGroupObjects_020baf38(int index)
{
    int i;
    GroupObject *object;
    VecFx32 offset;

    if (g_activeState_020bc800->groups[index].counter < g_activeState_020bc800->groups[index].limit) {
        i = 0;
        offset = MakeVec(0, 0, GetNegatedCombinedOffset_020bc68c(0));
        for (; i < g_activeState_020bc800->groups[index].objectCount; i++) {
            object = &g_activeState_020bc800->groups[index].objects[i];
            g_activeState_020bc800->groups[index].position = AddVec(&g_activeState_020bc800->groups[index].position, &offset);
            MoveShape(&object->shape, AddVec(object->shape.data, &offset));
            OffsetBoxByDelta_0203ac70(&object->shape.bounds, &object->box, &object->delta);
        }
        g_activeState_020bc800->groups[index].hidden = 0;
        if (g_activeState_020bc800->groups[index].counter != 0xff) {
            g_activeState_020bc800->groups[index].counter--;
        }
        return TRUE;
    }
    return FALSE;
}


