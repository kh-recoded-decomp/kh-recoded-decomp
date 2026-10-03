#include "nitro/types.h"

typedef struct {
    u8 data[0x88];
} GroupObject;

typedef struct {
    u8 pad_00[0x2];
    u8 objectCount;
    u8 pad_03[0x15];
    GroupObject *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x56];
    u8 groupCount;
    u8 pad_57[0xd];
    ObjectGroup *groups;
} OverlayState;

typedef struct {
    u32 unk_00;
    int **trees;
} WorldState;

extern OverlayState *g_activeState_020bc800;
extern WorldState *func_02036230(void);
extern void QuadTree_RemoveObject_02033c60(int *tree, GroupObject *object);

void RemoveGroupObjectsFromTree_020bbde4(void)
{
    WorldState *world = func_02036230();
    int group;
    int i;

    for (group = 1; group < g_activeState_020bc800->groupCount; group++) {
        for (i = 0; i < g_activeState_020bc800->groups[group].objectCount; i++) {
            QuadTree_RemoveObject_02033c60(*world->trees, &g_activeState_020bc800->groups[group].objects[i]);
        }
    }
}
