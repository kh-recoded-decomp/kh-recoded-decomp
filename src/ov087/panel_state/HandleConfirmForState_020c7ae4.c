#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0x10];
    int scrollDirection;
    u8 pad_014[0xb5c];
    PanelStackEntry stack[6];
    int depth;
} PanelScene;

extern PanelScene *func_ov039_020bc618(void);
extern void PushEntryConfirmState_020c6fd8(PanelScene *scene);
extern void func_ov087_020c6218(PanelScene *scene, int action);

void HandleConfirmForState_020c7ae4(void)
{
    PanelScene *scene = func_ov039_020bc618();

    if (scene->scrollDirection != 0 && scene->stack[scene->depth].stateId != 0x10) {
        return;
    }
    switch (scene->stack[scene->depth].stateId) {
    case 1:
    case 2:
    case 3:
        PushEntryConfirmState_020c6fd8(scene);
        break;
    case 0x10:
    case 0x11:
        func_ov087_020c6218(scene, 7);
        break;
    }
}
