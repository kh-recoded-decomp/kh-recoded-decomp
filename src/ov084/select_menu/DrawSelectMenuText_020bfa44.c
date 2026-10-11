#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct SelectMenu {
    u8 selection;
    u8 enabledMask;
    u8 dirty;
    u8 pad3;
    TextLayer titleLayer;
    TextLayer optionLayer;
    TextLayer helpLayer;
    const u16 *optionText[2];
    const u16 *helpText[2];
} SelectMenu;

extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);
extern void DrawTextColored_02001668(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);

void DrawSelectMenuText_020bfa44(SelectMenu *menu)
{
    s16 i = 0;

    CallVirtualHandlerSlot1_02001574(&menu->optionLayer, 0);
    CallVirtualHandlerSlot1_02001574(&menu->helpLayer, 0);
    for (; i < 2; i++) {
        const u16 *text = menu->optionText[i];
        int color = ((1 << i) & menu->enabledMask) ? 2 : 4;
        DrawTextAnchored_020015a0(&menu->optionLayer, (i == menu->selection) ? 8 : 0, i * 24 + 11, color, 8, text);
    }
    DrawTextColored_02001668(&menu->helpLayer, 2, 0, 2, 10, menu->helpText[menu->selection]);
    Text_UploadTileBuffer_02001520(&menu->optionLayer);
    Text_UploadTileBuffer_02001520(&menu->helpLayer);
    Text_UploadTileBuffer_02001520(&menu->titleLayer);
}
