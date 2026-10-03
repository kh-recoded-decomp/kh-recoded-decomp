#include "nitro/types.h"

typedef struct RecordEntry {
    u8 pad_00[0x2c];
    const u16 *name;
} RecordEntry;

typedef struct StatusPanel {
    u8 pad_000[0x1cc];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
} StatusPanel;

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01[3];
    u16 digitBase;
    u16 numberBase;
    u8 pad_08[0xb44 - 0x08];
    StatusPanel panel;
    u8 pad_d48[0x10dc - 0xd48];
    void *recordPool;
    void *container;
    u8 pad_10e4[0x11cc - 0x10e4];
    u8 strings[1];
} StatusMenu;

extern int func_ov073_020c3fa4(StatusPanel *panel);
extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void *func_ov039_020bc9ac(void);
extern void *func_ov039_020bc994(void);
extern void func_0200160c(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern RecordEntry *GetRecordSlotPair1Entry_02051ef4(int index);
extern int func_02001908(void *layer, const u16 *text, const u16 **next);
extern void Obj_SetField14_02001490(void *layer, void *font);
extern void DrawTextColored_02001668(void *layer, int x, int y, int color, int altColor, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void SetDigitDisplay_020be2c8(void *cells, int first, int value, void *origin);
extern void func_ov039_020be450(void *cells, int first, int value, void *origin);

void ShowSelectedRecordName_020c1a00(StatusMenu *menu)
{
    StatusPanel *panel;
    int maxWidth = 0;
    int recordIndex;
    const u16 *text;
    int width;

    if (menu->mode == 4) {
        panel = &menu->panel;
        recordIndex = func_ov073_020c3fa4(panel);
        SetStatusElementVisible_020beb5c(0xe, TRUE);
        CallVirtualHandlerSlot1_02001574(panel->textLayer, 0);
        if (recordIndex == -1) {
            func_0200160c(panel->textLayer, 4, 0, 2, 0x209, func_ov027_020ba2a8(menu->strings, 0x24),
                          func_ov039_020bc9ac(), 0xe4);
        } else {
            text = GetRecordSlotPair1Entry_02051ef4(recordIndex)->name;
            do {
                width = func_02001908(panel->textLayer, text, &text);
                if (maxWidth < width) {
                    maxWidth = width;
                }
            } while (text != NULL);
            if (maxWidth > 0xe4) {
                Obj_SetField14_02001490(panel->textLayer, func_ov039_020bc9ac());
            }
            DrawTextColored_02001668(panel->textLayer, 4, 0, 2, 10, GetRecordSlotPair1Entry_02051ef4(recordIndex)->name);
            Obj_SetField14_02001490(panel->textLayer, func_ov039_020bc994());
        }
        FlushBufferAndRunCallback_0200153c(panel->textLayer);
        panel->selectedRecord = recordIndex;
        return;
    }
    TagTracker_InvokeCallback_020b8210(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 10));
    SetStatusElementVisible_020beb5c(6, FALSE);
    SetStatusElementVisible_020beb5c(7, FALSE);
    SetDigitDisplay_020be2c8(menu->container, menu->digitBase, -1, NULL);
    func_ov039_020be450(menu->container, menu->numberBase, -1, NULL);
}
