#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 position;
    u8 pad_b0[0x104 - 0xb0];
} SceneNode;

typedef struct {
    u8 pad_0000[0x964];
    VecFx32 effectPos;
    u8 pad_0970[0x1700 - 0x970];
    SceneNode *nodes;
} Actor;

typedef struct {
    u8 pad_00[8];
    u8 pending;
} DrawRequest;

extern void SceneNode_Draw(SceneNode *node);

void Actor_DrawPendingEffectNode(Actor *actor, DrawRequest *request)
{
    VecFx32 position = actor->effectPos;
    SceneNode *node = NULL;

    if (request->pending & 1) {
        request->pending &= ~1;
        node = &actor->nodes[0];
    } else if (request->pending & 2) {
        request->pending &= ~2;
        node = &actor->nodes[1];
    } else if (request->pending & 4) {
        request->pending &= ~4;
        node = &actor->nodes[2];
    }
    if (node != NULL) {
        node->position = position;
        SceneNode_Draw(node);
    }
}
