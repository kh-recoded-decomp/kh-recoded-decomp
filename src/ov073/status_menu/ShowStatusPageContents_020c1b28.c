#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28d0];
    int munny;
} SaveData;

typedef struct StatusPanel {
    u8 pad_000[0x1cc];
    u8 textLayer[0x10dc - 0xd10];
} StatusPanel;

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01;
    u8 refreshCount;
    u8 pad_03;
    u16 digitBase;
    u16 numberBase;
    u8 pad_08[4];
    int numberValue;
    u8 pad_10[0xb44 - 0x10];
    StatusPanel panel;
    void *recordPool;
    void *container;
    u8 pad_10e4[0x11cc - 0x10e4];
    u8 strings[1];
} StatusMenu;

extern SaveData *data_0205fe0c;

extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern void func_ov039_020bc914(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void SetDigitDisplay_020be2c8(void *cells, int first, int value, void *origin);
extern void func_ov039_020be450(void *cells, int first, int value, void *origin);
extern void ResetStatusHeaderText_020beb7c(StatusMenu *menu);

void ShowStatusPageContents_020c1b28(StatusMenu *menu)
{
    if (menu->mode == 4) {
        StatusPanel *panel = &menu->panel;

        SetStatusElementVisible_020beb5c(0xe, FALSE);
        CallVirtualHandlerSlot1_02001574(panel->textLayer, 0);
        DrawTextAnchored_020015a0(panel->textLayer, 4, 0, 2, 8, func_ov027_020ba2a8(menu->strings, 0));
        FlushBufferAndRunCallback_0200153c(panel->textLayer);
        return;
    }
    func_ov039_020bc914();
    InvokeCallback40_020b8268(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 10));
    SetStatusElementVisible_020beb5c(6, TRUE);
    SetStatusElementVisible_020beb5c(7, TRUE);
    SetDigitDisplay_020be2c8(menu->container, menu->digitBase, data_0205fe0c->munny, NULL);
    func_ov039_020be450(menu->container, menu->numberBase, menu->numberValue, NULL);
    ResetStatusHeaderText_020beb7c(menu);
    menu->refreshCount++;
}
