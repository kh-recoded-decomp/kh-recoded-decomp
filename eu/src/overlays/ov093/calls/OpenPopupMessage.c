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

extern PopupManager *data_ov093_020c5104;
extern void SetBgSubLayerVisible(PopupState *popup, BOOL visible);
extern void DispatchByPartType(int layer, u16 *data, int type, int *params, int value, int flags);
extern Size2D MeasurePopupTiles(PopupState *popup, const void *text, TextFrame *frame, int padX, int padY);
extern void StateMachine_SetState(PopupState *machine, int state);

void OpenPopupMessage(PopupState *popup)
{
    SetBgSubLayerVisible(popup, FALSE);
    DispatchByPartType(6, data_ov093_020c5104->partData, data_ov093_020c5104->partType,
                                data_ov093_020c5104->partParams, 0x1d, 0);
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
        Size2D size = MeasurePopupTiles(popup, popup->text, &popup->frame, 0, 0);

        popup->frame.width = size.width;
        popup->frame.height = size.height;
        popup->frame.x = 16 - popup->frame.width / 2;
        popup->frame.y = 12 - popup->frame.height / 2;
    }
    popup->frameCount = 0;
    popup->frame.textArg = popup->textArg;
    StateMachine_SetState(popup, 3);
}
