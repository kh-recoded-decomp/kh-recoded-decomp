#include "nitro/types.h"
#include "ov014/PanelTouchOffsets.h"

typedef struct PanelObjects {
    u8 reserved[0x647c];
} PanelObjects;

typedef struct PanelCategoryLayout {
    u8 reserved00[0x1d4];
    u8 hitGroupIds[22][16];
    u8 priorities[22][16];
    u8 groupCounts[22];
} PanelCategoryLayout;

typedef struct PanelState {
    u8 reserved00[0x6514];
    PanelObjects subObjects;
    u8 reservedC990[0xcab8 - 0xc990];
    PanelCategoryLayout *layout;
} PanelState;

typedef struct HitEntry {
    u8 hitGroupId;
    u8 category;
} HitEntry;

extern PanelState *g_panelState_0206f9a0;
extern void MI_CpuFill8(void *destination, int value, u32 size);
extern BOOL HitTestPanelGroup(PanelObjects *objects, int groupId, int x, int y);

int HitTestCategoryPanel_0206f42c(int x, int y)
{
    PanelState *state = g_panelState_0206f9a0;
    PanelCategoryLayout *layout = state->layout;
    PanelObjects *objects = &state->subObjects;
    s16 hits[5];
    PanelTouchOffsets offsets = gPanelTouchProbeOffsets.samples;
    HitEntry lookup[200];
    int category;
    int item;
    int point;
    int priority;
    int best;

    MI_CpuFill8(lookup, 0, sizeof(lookup));
    /* Each priority has room for the first two groups using that priority. */
    for (category = 0; category < 22; category++) {
        for (item = 0; item < layout->groupCounts[category]; item++) {
            u8 doubledPriority = layout->priorities[category][item] * 2;
            if (lookup[doubledPriority].hitGroupId == 0) {
                lookup[doubledPriority].hitGroupId = layout->hitGroupIds[category][item];
                lookup[doubledPriority].category = category;
            } else {
                HitEntry *hit = &lookup[doubledPriority];
                if (hit[1].hitGroupId == 0) {
                    hit[1].hitGroupId = layout->hitGroupIds[category][item];
                    hit[1].category = category;
                }
            }
        }
    }

    /* Probe the touch point and its four diagonal neighbours, front to back. */
    for (point = 0; point < 5; point++) {
        hits[point] = -1;
        int dx = offsets.coordinates[point * 2];
        int hitX = x + dx;
        int dy = offsets.coordinates[point * 2 + 1];
        for (priority = 199; priority >= 0; priority--) {
            if (lookup[priority].hitGroupId != 0 && HitTestPanelGroup(objects,
                lookup[priority].hitGroupId, hitX, y + dy)) {
                hits[point] = priority;
                break;
            }
        }
    }

    best = -1;
    for (point = 0; point < 5; point++) {
        if (hits[point] > best) {
            best = hits[point];
        }
    }
    if (best >= 0) {
        return lookup[best].category;
    }
    return -1;
}
