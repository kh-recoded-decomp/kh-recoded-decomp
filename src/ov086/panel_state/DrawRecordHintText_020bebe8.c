#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x74];
    u8 hintLayer[0xc0];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    u8 pad_140[0x150 - 0x140];
    BOOL hasSubPages;
} Ov086Menu;

extern void CallVirtualHandlerSlot1_02001574(void *obj, int arg);
extern BOOL func_ov086_020c2080(int page);
extern const u16 *func_ov027_020ba2a8(Ov086Menu *menu, int index);
extern void DrawTextAnchored_020015a0(void *obj, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(void *surface);

void DrawRecordHintText_020bebe8(Ov086Menu *menu)
{
    int y = 0;
    BOOL showStep = FALSE;

    CallVirtualHandlerSlot1_02001574(menu->hintLayer, 0);
    if (!func_ov086_020c2080(menu->pageIndex)) {
        DrawTextAnchored_020015a0(menu->hintLayer, 0, y, 2, 0x209, func_ov027_020ba2a8(menu, 0));
        y += 0xc;
    }
    if (menu->hasSubPages != 0) {
        DrawTextAnchored_020015a0(menu->hintLayer, 0, y, 2, 0x209, func_ov027_020ba2a8(menu, 2));
        switch (menu->pageIndex) {
        case 6:
            if (menu->stepCount == 1) {
                showStep = TRUE;
            }
            break;
        case 7:
            break;
        default:
            if (menu->stepCount >= 1) {
                showStep = TRUE;
            }
            break;
        }
        if (showStep) {
            DrawTextAnchored_020015a0(menu->hintLayer, 0, y + 0xc, 2, 0x209, func_ov027_020ba2a8(menu, 3));
        }
    } else {
        DrawTextAnchored_020015a0(menu->hintLayer, 0, y, 2, 0x209, func_ov027_020ba2a8(menu, 1));
    }
    Text_UploadTileBuffer_02001520(menu->hintLayer);
}
