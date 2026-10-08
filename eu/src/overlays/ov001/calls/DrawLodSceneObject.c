#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LodRanges {
    u8 pad[0x68];
    fx32 farEnter;
    fx32 farExit;
} LodRanges;

typedef struct LodModel {
    u8 pad[0x14];
    u8 node[1];
} LodModel;

typedef struct LodObject {
    u8 pad0[8];
    LodRanges *ranges;
    LodModel *nearModel;
    void *farNode;
    u8 pad14[0x2c];
    VecFx32 position;
    u16 unk4c;
    u16 flags;
} LodObject;

extern VecFx32 *func_ov021_020af5d4(void);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void SceneNode_Draw(void *node);

void DrawLodSceneObject(LodObject *object) {
    fx32 distance = VEC_Distance(func_ov021_020af5d4(), &object->position);

    if (object->flags & 0x8000) {
        if (distance <= object->ranges->farExit) {
            object->flags &= ~0x8000;
        }
    } else {
        if (object->ranges->farEnter <= distance) {
            object->flags |= 0x8000;
        }
    }
    SceneNode_Draw((object->flags & 0x8000) ? object->farNode : object->nearModel->node);
}
