#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneNode {
    struct SceneNode *next;
    u8 pad_04[0x2a];
    s8 state : 4;
    s8 unk2e_4 : 4;
    u8 useRange : 1;
    u8 locked : 1;
    u8 unk2f_2 : 6;
    u8 pad_30[2];
    s16 timer;
    fx32 range;
    VecFx32 position;
} SceneNode;

typedef struct {
    u8 pad_00[0x4c];
    SceneNode *nodes;
} SceneNodeList;

extern SceneNodeList *data_ov001_020a0464;
extern BOOL IsEntryFlag2Active_020642d0(void);
extern VecFx32 *func_ov001_0206dc4c(int target);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void SetNodeStateRandomDir_0206604c(SceneNode *node, int target);

void WakeNearbyIdleNodes_02066874(int target)
{
    SceneNode *node;

    if (IsEntryFlag2Active_020642d0()) {
        return;
    }
    for (node = data_ov001_020a0464->nodes; node != NULL; node = node->next) {
        if (!node->locked && node->state < 0 && node->timer == 0) {
            BOOL inRange = TRUE;
            if (node->useRange) {
                fx32 limit = node->range + 0x800;
                if (limit < func_01ffa0f4(&node->position, func_ov001_0206dc4c(target))) {
                    inRange = FALSE;
                }
            }
            if (inRange) {
                SetNodeStateRandomDir_0206604c(node, target);
            }
        }
    }
}
