#include "nitro/types.h"

typedef struct SceneNode {
    u8 pad_00[0x2c];
    u8 groupId;
    u8 pad_2D;
    s8 state : 4;
    s8 direction : 4;
    u8 pad_2F;
    u16 timer;
} SceneNode;

extern u32 func_0202a9d0(u32 range);
extern void func_ov001_02066004(u8 groupId);

void SetNodeStateRandomDir_0206604c(SceneNode *node, int state)
{
    u32 roll;
    int direction;

    node->state = state;
    node->timer = 0;
    roll = func_0202a9d0(2);
    direction = -1;
    if (roll == 0) {
        direction = 1;
    }
    node->direction = direction;
    func_ov001_02066004(node->groupId);
}
