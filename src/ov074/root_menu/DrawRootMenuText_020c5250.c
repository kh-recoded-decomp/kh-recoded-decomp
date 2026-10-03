#include "nitro/types.h"

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct MenuEntry {
    u16 *label;
    u16 *description;
    int id;
} MenuEntry;

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04[0x12 - 0x04];
    u16 unlockMessage;
    u8 pad_14[0x438 - 0x14];
    TextWindow windows[4];
    MenuEntry entries[8];
    u16 *extraLabels[4];
    u8 pad_578[0x5dc - 0x578];
    u8 strings[0xc];
} RootMenu;

extern void CallVirtualHandlerSlot1_02001574(TextWindow *window, int arg);
extern int func_ov039_020bc9ac(void);
extern void func_0200160c(TextWindow *window, u32 x, u32 y, u32 color, u32 flags, u16 *text, int override, int width);
extern void DrawTextAnchored_020015a0(TextWindow *window, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored_02001668(TextWindow *window, int x, int y, int color, int altColor, const u16 *text);
extern void DrawTextPackedColor_0200174c(TextWindow *window, int x, int y, int color, int flags, int highColor, const u16 *text);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void Text_UploadTileBuffer_02001520(TextWindow *window);

void DrawRootMenuText_020c5250(RootMenu *menu)
{
    s16 i = 0;

    CallVirtualHandlerSlot1_02001574(&menu->windows[1], 0);
    CallVirtualHandlerSlot1_02001574(&menu->windows[2], 0);
    CallVirtualHandlerSlot1_02001574(&menu->windows[3], 0);
    if (menu->mode == 0) {
        for (; i < menu->entryCount; i++) {
            func_0200160c(&menu->windows[1], (i == menu->cursor) ? 8 : 0, i * 16 + 3, 2, 8, menu->entries[i].label,
                          func_ov039_020bc9ac(), 0x5c);
        }
    }
    switch (menu->mode) {
    case 1:

        DrawTextAnchored_020015a0(&menu->windows[3], 0x68, 0xb, 2, 0x10, menu->extraLabels[0]);
        DrawTextAnchored_020015a0(&menu->windows[3], 0x3c, 0x1b, 2, 0x10, menu->extraLabels[1]);
        DrawTextAnchored_020015a0(&menu->windows[3], 0x94, 0x1b, 2, 0x10, menu->extraLabels[2]);
        DrawTextColored_02001668(&menu->windows[2], 5, 0, 2, 10, menu->extraLabels[3]);
        break;
    case 2:
        DrawTextPackedColor_0200174c(&menu->windows[3], 0, 0, 2, 6, 10, func_ov027_020ba2a8(menu->strings, menu->unlockMessage));
        break;
    case 0:
        DrawTextColored_02001668(&menu->windows[2], 5, 0, 2, 10, menu->entries[menu->cursor].description);
        break;
    }
    Text_UploadTileBuffer_02001520(&menu->windows[1]);
    Text_UploadTileBuffer_02001520(&menu->windows[2]);
    Text_UploadTileBuffer_02001520(&menu->windows[0]);
    Text_UploadTileBuffer_02001520(&menu->windows[3]);
}
