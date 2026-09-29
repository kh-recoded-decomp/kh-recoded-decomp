#include "nitro/types.h"

typedef struct CollisionShape {
    u8 pad_00[0x6c];
    s32 objectType;
} CollisionShape;

typedef struct CollisionObject {
    CollisionShape *shape;
    s32 category;
} CollisionObject;

extern s8 GetCtxModeByte_02068084(void);
extern s32 ContainsMatchingEntry_02034900(CollisionObject *object, u32 kind);

BOOL CameraCollision_ShouldBlock_020c320c(CollisionObject *object)
{
    if (GetCtxModeByte_02068084() == 5 && object->category == 4 &&
        object->shape->objectType == 0x1e) {
        return TRUE;
    }
    if (ContainsMatchingEntry_02034900(object, 4)) {
        return FALSE;
    }
    if (object->category == 4 &&
        (object->shape->objectType == 1 || object->shape->objectType == 0x17)) {
        return FALSE;
    }
    return TRUE;
}
