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

extern VecFx32 *func_ov021_020af5b4(void);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void SceneNode_Draw_01ffb12c(void *node);

void DrawLodSceneObject_0207f258(LodObject *object) {
    fx32 distance = func_01ffa0f4(func_ov021_020af5b4(), &object->position);

    if (object->flags & 0x8000) {
        if (distance <= object->ranges->farExit) {
            object->flags &= ~0x8000;
        }
    } else {
        if (object->ranges->farEnter <= distance) {
            object->flags |= 0x8000;
        }
    }
    SceneNode_Draw_01ffb12c((object->flags & 0x8000) ? object->farNode : object->nearModel->node);
}
