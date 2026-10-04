#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
    int textId;
    int textArg;
    u8 pad_14[4];
    u8 textBox[0x38];
    u16 tileX;
    u16 tileY;
    u16 offsetX;
    u16 offsetY;
} PopupState;

typedef struct {
    u8 pad_00[0x10];
    int slotIndex;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern void func_ov093_020c2e04(PopupState *popup);
extern int func_020019f4(void *textBox);
extern void func_ov093_020c308c(int slotIndex, int x, int y, int textId, int textArg);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov093_020c317c(int slotIndex, BOOL visible);
extern void StateMachine_SetState_020c3bc4(PopupState *machine, int state);

void OpenPopupWindow_020c3418(PopupState *popup)
{
    int lineHeight;

    func_ov093_020c2e04(popup);
    lineHeight = func_020019f4(popup->textBox);
    func_ov093_020c308c(g_popupManager_020c50e4->slotIndex, (popup->tileX + popup->offsetX) * 8,
                        (popup->tileY + popup->offsetY) * 8 + lineHeight / 2 - 4, popup->textId, popup->textArg);
    PlaySoundEffect_0204d924(0, 9);
    func_ov093_020c317c(g_popupManager_020c50e4->slotIndex, TRUE);
    StateMachine_SetState_020c3bc4(popup, 5);
}
