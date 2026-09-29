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

typedef struct FontSlot {
    NNSG2dFont font;
    void *file;
} FontSlot;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct MessageLine {
    void *line;
    s32 messageId;
} MessageLine;

typedef struct HudContext {
    u8 pad_000[0x78];
    FontSlot labelFont;
    FontSlot narrowFont;
    u8 pad_090[0xa8 - 0x90];
    TextWindow messageWindow;
    MessageLine messageLines[22];
} HudContext;

extern const TextFrame data_ov001_0209dc04;
extern const u16 data_ov001_0209ed6c[];
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);
extern const u16 *func_ov027_020ba2a8(MessageSet *messages, int index);
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void *GetWord20_020019f0(void *window);
extern void *func_02001914(void *window, int selectAsCurrent, int alignFromEnd);
extern void func_0200160c(void *window, int x, int y, int color, int flags, const u16 *text, void *narrowFont, int maxWidth);
extern void FreePointerIfSet_020ba294(void **pointer);

void BuildMessageLineWindow_0206f324(HudContext *context, const s32 *messageIds)
{
    TextFrame frame = data_ov001_0209dc04;
    MessageSet messages;
    const u16 *text;
    int i;

    func_ov027_020ba25c(&messages, func_ov001_02073634(3), 1);
    if (messageIds[0] >= 0) {
        text = func_ov027_020ba2a8(&messages, messageIds[0]);
    } else {
        text = data_ov001_0209ed6c;
    }
    InitTextLayerAt_020014b0(&context->messageWindow, 3, NULL, &context->labelFont.font, &frame);
    func_0200160c(&context->messageWindow, 0x4f, 1, 1, 0x821, text, &context->narrowFont, 0x50);
    func_0200160c(&context->messageWindow, 0x4e, 0, 2, 0x821, text, &context->narrowFont, 0x50);
    context->messageLines[0].line = GetWord20_020019f0(&context->messageWindow);
    context->messageLines[0].messageId = messageIds[0];
    for (i = 1; i < 22; i++) {
        if (messageIds[i] >= 0) {
            text = func_ov027_020ba2a8(&messages, messageIds[i]);
        } else {
            text = data_ov001_0209ed6c;
        }
        context->messageLines[i].line = func_02001914(&context->messageWindow, 1, 0);
        func_0200160c(&context->messageWindow, 0x4f, 1, 1, 0x821, text, &context->narrowFont, 0x50);
        func_0200160c(&context->messageWindow, 0x4e, 0, 2, 0x821, text, &context->narrowFont, 0x50);
        context->messageLines[i].messageId = messageIds[i];
    }
    FreePointerIfSet_020ba294(&messages.file);
}
