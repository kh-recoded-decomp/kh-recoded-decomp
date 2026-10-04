#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    int kind;
    u8 pad[0x104];
} PanelModelSlot;

typedef struct {
    u8 pad0[4];
    int selectedSlot;
    u8 pad1[0x118 - 0x8];
    PanelModelSlot slots[10];
    u8 pad2[0xb70 - 0x118 - 10 * 0x108];
    PanelStackEntry stack[6];
    int depth;
    u8 pad3[0xbc0 - 0xba4];
    int confirmFlag;
    int cancelFlag;
    int currentKind;
    int requiredKind;
} PanelScene;

typedef struct {
    u8 pad[0xc];
    int mode;
} FocusElement;

extern void *func_ov039_020bc1bc(void);
extern FocusElement *func_ov027_020b90f4(void *container);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void PushPanelState_020c61b0(PanelScene *scene, int stateId);

void ConfirmPanelSelection_020c6dcc(PanelScene *scene)
{
    int kind = scene->slots[scene->selectedSlot].kind;

    switch (scene->stack[scene->depth].stateId) {
    case 1:
        if (kind == 7) {
            scene->confirmFlag = TRUE;
            if (IsGlobalPackedBitSet_02027304(0x4436) && scene->requiredKind == kind) {
                PushPanelState_020c61b0(scene, 4);
                return;
            }
            PushPanelState_020c61b0(scene, 5);
            scene->cancelFlag = TRUE;
        } else if (kind == scene->currentKind) {
            scene->confirmFlag = FALSE;
            PushPanelState_020c61b0(scene, 0xf);
        } else {
            scene->confirmFlag = TRUE;
            if (IsGlobalPackedBitSet_02027304(0x4436) && scene->requiredKind == kind) {
                PushPanelState_020c61b0(scene, 4);
                return;
            }
            PushPanelState_020c61b0(scene, 5);
            scene->cancelFlag = TRUE;
        }
        break;
    case 2:
        if (kind == scene->currentKind && func_ov027_020b90f4(func_ov039_020bc1bc())->mode == 2) {
            scene->confirmFlag = FALSE;
            PushPanelState_020c61b0(scene, 0xa);
            return;
        }
        scene->confirmFlag = TRUE;
        if (kind == scene->requiredKind) {
            scene->cancelFlag = TRUE;
            PushPanelState_020c61b0(scene, 6);
        } else {
            PushPanelState_020c61b0(scene, 5);
            scene->cancelFlag = TRUE;
        }
        break;
    case 3:
        if ((kind == 7 && func_ov027_020b90f4(func_ov039_020bc1bc())->mode == 2) ||
            (kind != 7 && kind == scene->currentKind)) {
            scene->confirmFlag = FALSE;
            PushPanelState_020c61b0(scene, 0xe);
            return;
        }
        scene->confirmFlag = TRUE;
        if (IsGlobalPackedBitSet_02027304(0x4436)) {
            if (scene->requiredKind == kind) {
                scene->cancelFlag = FALSE;
                PushPanelState_020c61b0(scene, 4);
            } else {
                scene->cancelFlag = TRUE;
                PushPanelState_020c61b0(scene, 5);
            }
        } else {
            scene->cancelFlag = TRUE;
            PushPanelState_020c61b0(scene, 6);
        }
        break;
    }
}
