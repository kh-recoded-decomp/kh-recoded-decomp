#include "nitro/types.h"

typedef struct ScrolledText {
    s32 state;
    u8 pad_04[0x38];
    u8 textLayer[0x34];
    const u16 *text;
    u8 pad_74[0xe];
    u16 lineSpacing;
    u8 pad_84[0x88];
    s32 *scrollLine;
} ScrolledText;

extern u8 func_020019f4(void *textLayer);
extern void CallVirtualHandlerSlot1_02001574(void *textLayer, int arg);
extern void DrawTextAnchored_020015a0(void *textLayer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(void *textLayer);

void RedrawScrolledTextLayer_020bf3d8(ScrolledText *view)
{
    s32 *scrollLine;
    int y;

    if (view->state != 1) {
        return;
    }
    scrollLine = view->scrollLine;
    y = func_020019f4(view->textLayer);
    y = -(*scrollLine * (y + view->lineSpacing));
    CallVirtualHandlerSlot1_02001574(view->textLayer, 1);
    DrawTextAnchored_020015a0(view->textLayer, 0x11, y + 1, 2, 0x209, view->text);
    DrawTextAnchored_020015a0(view->textLayer, 0x10, y, 3, 0x209, view->text);
    FlushBufferAndRunCallback_0200153c(view->textLayer);
}
