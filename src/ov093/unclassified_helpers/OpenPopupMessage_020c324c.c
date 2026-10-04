#include "nitro/types.h"

#define REG_DB_BG2OFS (*(vu32 *)0x04001018)

typedef struct {
    int width;
    int height;
} Size2D;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 textArg;
    u16 palette;
    u16 unk_0c;
    u16 unk_0e;
} TextFrame;

typedef struct {
    int state;
    u32 flags;
    int frameCount;
    int scrollX;
    int scrollY;
    int textArg;
    u8 pad_18[0x34];
    const u16 *text;
    TextFrame frame;
} PopupState;

typedef struct {
    u8 pad_00[0x20];
    u16 *partData;
    int partType;
    int *partParams;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern void SetBgSubLayerVisible_020c3b5c(PopupState *popup, BOOL visible);
extern void DispatchByPartType_0202b4c0(int layer, u16 *data, int type, int *params, int value, int flags);
extern Size2D func_ov093_020c2f88(PopupState *popup, const void *text, TextFrame *frame, int padX, int padY);
extern void StateMachine_SetState_020c3bc4(PopupState *machine, int state);

void OpenPopupMessage_020c324c(PopupState *popup)
{
    SetBgSubLayerVisible_020c3b5c(popup, FALSE);
    DispatchByPartType_0202b4c0(6, g_popupManager_020c50e4->partData, g_popupManager_020c50e4->partType,
                                g_popupManager_020c50e4->partParams, 0x1d, 0);
    REG_DB_BG2OFS = (-popup->scrollX & 0x1ff) | ((-popup->scrollY << 16) & 0x1ff0000);
    popup->frame.x = 10;
    popup->frame.y = 9;
    popup->frame.width = 12;
    popup->frame.height = 7;
    popup->frame.textArg = 0;
    popup->frame.palette = 15;
    popup->frame.unk_0c = 0;
    popup->frame.unk_0e = 2;
    {
        Size2D size = func_ov093_020c2f88(popup, popup->text, &popup->frame, 0, 0);

        popup->frame.width = size.width;
        popup->frame.height = size.height;
        popup->frame.x = 16 - popup->frame.width / 2;
        popup->frame.y = 12 - popup->frame.height / 2;
    }
    popup->frameCount = 0;
    popup->frame.textArg = popup->textArg;
    StateMachine_SetState_020c3bc4(popup, 3);
}
