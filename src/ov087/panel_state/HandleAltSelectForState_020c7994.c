#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u32 id;
    u8 model[0x104];
} ListEntry;

typedef struct {
    int step;
    int cursor;
    int entryCount;
    int scrollX;
    int scrollDirection;
    u8 pad_014[0x104];
    ListEntry entries[8];
    u8 pad_958[0x218];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0x1c];
    int pendingChoice;
    int confirmFlag;
    int lockedId;
} PanelScene;

extern PanelScene *func_ov039_020bc618(void);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern BOOL func_ov039_020bc810(void);
extern void PushPanelState_020c61b0(PanelScene *scene, int stateId);
extern void PopPanelState_020c6218(PanelScene *scene, int soundIndex);
extern void ConfirmPanelSelection_020c6dcc(PanelScene *scene);
extern void PushEntryConfirmState_020c6fd8(PanelScene *scene);

void HandleAltSelectForState_020c7994(void)
{
    PanelScene *scene = func_ov039_020bc618();
    int entryId = scene->entries[scene->cursor].id;

    ReadSessionPackedBits_02064574(0x1a00, 2);
    if (scene->scrollDirection != 0 && scene->stack[scene->depth].stateId != 0x10) {
        return;
    }
    switch (scene->stack[scene->depth].stateId) {
    case 1:
        if (entryId == 6) {
            PushEntryConfirmState_020c6fd8(scene);
        } else if (entryId == 7) {
            if (!func_ov039_020bc810()) {
                ConfirmPanelSelection_020c6dcc(scene);
            } else {
                PushEntryConfirmState_020c6fd8(scene);
            }
        } else {
            ConfirmPanelSelection_020c6dcc(scene);
        }
        break;
    case 2:
    case 3:
        if (entryId == 6) {
            PushEntryConfirmState_020c6fd8(scene);
        } else {
            ConfirmPanelSelection_020c6dcc(scene);
        }
        break;
    case 4:
        PushPanelState_020c61b0(scene, 7);
        scene->confirmFlag = 0;
        break;
    case 0xc:
        PushPanelState_020c61b0(scene, 0xb);
        scene->confirmFlag = 1;
        break;
    case 0x10:
    case 0x11:
        PopPanelState_020c6218(scene, 7);
        break;
    }
}