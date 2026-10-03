#include "nitro/types.h"

typedef struct PanelNode {
    u8 pad_00[8];
    u8 *entity;
    u8 pad_0c[0x32 - 0x0c];
    u8 actorId;
    u8 pad_33[0x48 - 0x33];
    void *animation;
    u8 pad_4c[4];
    u8 state;
    u8 pad_51[3];
    u16 flags;
} PanelNode;

extern u16 AdvanceAnimationTracks_0202ef24(void *state, int delta);
extern u8 *func_02036240(u32 actorId);
extern void Obj_RemoveFromQuadTree_020355f4(void *entity);

int UpdatePanelAnimations_020a2ef8(PanelNode *node)
{
    if ((node->flags & 0x20) && AdvanceAnimationTracks_0202ef24(node->animation, 0x1000)) {
        node->flags &= 0xffdf;
    }
    if (node->flags & 0x10) {
        if (AdvanceAnimationTracks_0202ef24(func_02036240(node->actorId) + 4, 0x1000)) {
            node->flags &= 0xffaf;
        }
    }
    if (!(node->flags & 0x30)) {
        node->state = 2;
        if (!(node->flags & 1)) {
            Obj_RemoveFromQuadTree_020355f4(node->entity + 0x10);
        }
    }
    return 0;
}
