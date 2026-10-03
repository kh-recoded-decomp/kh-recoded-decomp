#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *buffer;
    void *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x28];
    void *buffer0;
    void *buffer1;
    void *items;
    void *buffer3;
    u8 pad_38[0x4];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x4c];
    void *stepCodes;
    ActiveRecord *records;
    u8 pad_54;
    u8 recordCount;
    u8 activeGroupCount;
    u8 groupCount;
    u8 pad_58[0x8];
    void *workBuffer;
    ObjectGroup *groups;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void FreeSceneRecords_020ba51c(void)
{
    int i;
    int count;

    if (g_activeState_020bc800->records != NULL) {
        count = g_activeState_020bc800->groupCount;
        for (i = 0; i < count; i++) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->groups[i].buffer);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->groups[i].objects);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->groups);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->stepCodes);
        for (i = 0; i < g_activeState_020bc800->recordCount; i++) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->records[i].buffer0);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->records[i].buffer1);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->records[i].items);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->records[i].buffer3);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->records);
        g_activeState_020bc800->records = NULL;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_activeState_020bc800->workBuffer);
    }
}
