#include "nitro/types.h"

#define REG_DB_BG2OFS (*(vu32 *)0x04001018)

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 param;
    u16 palette;
    u16 field_0c;
    u16 field_0e;
} TextFrame;

typedef struct {
    int width;
    int height;
} TextSize;

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
    s32 x;
    s32 y;
    s32 param;
    u8 pad_18[0x34];
    u16 *text;
    TextFrame frame;
} PopupWindow;

typedef struct {
    u8 pad_00[0x20];
    void *partData;
    int partCount;
    void *partTable;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void SetSubBg2Visible(PopupWindow *window, BOOL enable);
extern void DispatchByPartType(int type, void *data, int count, void *table, int tile, int offset);
extern TextSize MeasurePopupTextTiles(PopupWindow *window, u16 *text, TextFrame *frame, int padX, int padY);
extern void SetPopupState(PopupWindow *window, s32 state);

void OpenPopupWindow_020c1e38(PopupWindow *window)
{
    TextSize frameSize;
    TextSize size;

    SetSubBg2Visible(window, FALSE);
    DispatchByPartType(6, data_ov091_020c375c->partData, data_ov091_020c375c->partCount,
                                data_ov091_020c375c->partTable, 0x1d, 0);
    REG_DB_BG2OFS = (-window->x & 0x1ff) | ((-window->y << 16) & 0x1ff0000);
    window->frame.x = 10;
    window->frame.y = 9;
    window->frame.width = 12;
    window->frame.height = 7;
    window->frame.param = 0;
    window->frame.palette = 15;
    window->frame.field_0c = 0;
    window->frame.field_0e = 2;
    size = MeasurePopupTextTiles(window, window->text, &window->frame, 0, 0);
    frameSize = size;
    window->frame.width = frameSize.width;
    window->frame.height = frameSize.height;
    window->frame.x = 16 - ((u32)window->frame.width >> 1);
    window->frame.y = 12 - ((u32)window->frame.height >> 1);
    window->stateTimer = 0;
    window->frame.param = window->param;
    SetPopupState(window, 3);
}
