#include "nitro/types.h"

typedef struct MenuStateCallbacks {
    void (*enter)(void);
    void (*update)(void);
    void (*leave)(void);
} MenuStateCallbacks;

typedef struct MenuContext {
    s8 state;
    s8 result;
    u8 pad_02[0x56c - 2];
    u8 listA[0x69e8 - 0x56c];
    u8 listB[4];
} MenuContext;

extern MenuContext *gOv002MenuWork;
extern MenuStateCallbacks gMenuStateTable[];
extern void ScrollMenuClouds(void);
extern void UpdateDriftingPanelWidgets(void);
extern void UpdateDisplayObjectListQueued(void *list);
extern u32 IsScreenFadeComplete(void);

int UpdateMenuContext(void)
{
    gMenuStateTable[gOv002MenuWork->state].update();
    ScrollMenuClouds();
    UpdateDriftingPanelWidgets();
    UpdateDisplayObjectListQueued(gOv002MenuWork->listA);
    UpdateDisplayObjectListQueued(gOv002MenuWork->listB);
    if (IsScreenFadeComplete()) {
        return gOv002MenuWork->result;
    }
    return 0;
}
