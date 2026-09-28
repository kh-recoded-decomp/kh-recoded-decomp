#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct HudContext {
    u8 pad_000[0x9c];
    NNSG2dFont menuFont;
    u8 pad_afterMenuFont[0x1f8 - 0x9c - sizeof(NNSG2dFont)];
    s32 choiceMenuActive;
    u8 choiceWindow[0x34];
    void *choiceLines[4];
} HudContext;

extern const TextFrame data_ov001_0209dc44;
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);
extern const void *func_ov027_020ba2a8(MessageSet *messages, int index);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *font, int hSpace, const void *text);
extern void func_020014b0(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void *GetWord20_020019f0(void *window);
extern void CallVirtualHandlerSlot1_02001574(void *window, int color);
extern void func_020015a0(void *window, int x, int y, int color, int flags, const void *text);
extern void *func_02001914(void *window, int selectAsCurrent, int alignFromEnd);
extern void FreePointerIfSet_020ba294(void **pointer);

void BuildChoiceWindow_0206f730(HudContext *context)
{
    int maxWidth = 0;
    MessageSet messages;
    TextFrame frame = data_ov001_0209dc44;
    int i;
    int columns;
    int centerX;

    func_ov027_020ba25c(&messages, func_ov001_02073634(5), 1);
    for (i = 0; i < 4; i++) {
        int width = G2D_MeasureTextWidth_02016bc0(&context->menuFont, 1, func_ov027_020ba2a8(&messages, i));
        if (maxWidth < width) {
            maxWidth = width;
        }
    }
    columns = (maxWidth + 7) / 8;
    if (columns > 16) {
        columns = 16;
    }
    if (columns == 0) {
        frame.width = 1;
    } else {
        frame.width = columns;
    }
    func_020014b0(context->choiceWindow, 3, 0, &context->menuFont, &frame);
    context->choiceLines[0] = GetWord20_020019f0(context->choiceWindow);
    CallVirtualHandlerSlot1_02001574(context->choiceWindow, 0xe);
    centerX = columns * 8 / 2;
    func_020015a0(context->choiceWindow, centerX, 3, 8, 0x411, func_ov027_020ba2a8(&messages, 0));
    for (i = 1; i < 4; i++) {
        context->choiceLines[i] = func_02001914(context->choiceWindow, 1, 0);
        CallVirtualHandlerSlot1_02001574(context->choiceWindow, 0xe);
        func_020015a0(context->choiceWindow, centerX, 3, 8, 0x411, func_ov027_020ba2a8(&messages, i));
    }
    FreePointerIfSet_020ba294(&messages.file);
    context->choiceMenuActive = 1;
}
