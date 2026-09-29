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

typedef struct SlotMessageIds {
    int ids[2];
} SlotMessageIds;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct HudContext {
    u8 pad_000[0x78];
    NNSG2dFont labelFont;
    u8 pad_afterLabelFont[0x9c - 0x78 - sizeof(NNSG2dFont)];
    NNSG2dFont menuFont;
    u8 pad_afterMenuFont[0x1fc - 0x9c - sizeof(NNSG2dFont)];
    TextWindow headerWindow;
    TextWindow slotWindows[3];
    MessageSet slotMessages;
    MessageSet statusMessages;
} HudContext;

extern const TextFrame data_ov001_0209dc54;
extern const SlotMessageIds data_ov001_0209db8c;
extern int func_ov001_0207123c(void *context);
extern int UpdateWidgetLayerDefault_020b9df0(int layer, int widget);
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);
extern const void *func_ov027_020ba2a8(MessageSet *messages, int index);
extern int CountAssignedFieldSlots_0207169c(void);
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1_02001574(void *window, int color);
extern void DrawTextAnchored_020015a0(void *window, int x, int y, int color, int flags, const void *text);
extern void FlushBufferAndRunCallback_0200153c(void *window);
extern void FreePointerIfSet_020ba294(void **pointer);

void BuildSlotLabelWindows_0206f858(HudContext *context)
{
    TextFrame frame = data_ov001_0209dc54;
    MessageSet messages;
    SlotMessageIds slotIds;
    int lineCount;
    void *charBase;
    int slotCount;
    int i;

    charBase = (void *)UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(context), 0xb);
    slotIds = data_ov001_0209db8c;
    InitTextLayerAt_020014b0(&context->headerWindow, 3, 0, &context->menuFont, &frame);
    func_ov027_020ba25c(&messages, func_ov001_02073634(0), 1);
    i = 1;
    slotCount = CountAssignedFieldSlots_0207169c();
    frame.x = 0x12;
    frame.y = 0x16 - slotCount * 2;
    frame.width = 5;
    frame.height = 1;
    frame.charBase = 0x3f0;
    if (slotCount == 0) {
        InitTextLayerAt_020014b0(&context->slotWindows[0], 3, charBase, &context->labelFont, &frame);
        CallVirtualHandlerSlot1_02001574(&context->slotWindows[0], 1);
        DrawTextAnchored_020015a0(&context->slotWindows[0], 0, 0, 2, 0, func_ov027_020ba2a8(&messages, 0));
        FlushBufferAndRunCallback_0200153c(&context->slotWindows[0]);
    } else {
        InitTextLayerAt_020014b0(&context->slotWindows[0], 3, charBase, &context->labelFont, &frame);
        CallVirtualHandlerSlot1_02001574(&context->slotWindows[0], 1);
        DrawTextAnchored_020015a0(&context->slotWindows[0], 0, 0, 2, 0, func_ov027_020ba2a8(&messages, 0x17));
        FlushBufferAndRunCallback_0200153c(&context->slotWindows[0]);
        frame.charBase += 5;
        frame.y += 2;
        lineCount = slotCount + 1;
        for (; i < lineCount; i++) {
            InitTextLayerAt_020014b0(&context->slotWindows[i], 3, charBase, &context->labelFont, &frame);
            CallVirtualHandlerSlot1_02001574(&context->slotWindows[i], 1);
            DrawTextAnchored_020015a0(&context->slotWindows[i], 0, 0, 2, 0, func_ov027_020ba2a8(&messages, slotIds.ids[i - 1]));
            FlushBufferAndRunCallback_0200153c(&context->slotWindows[i]);
            frame.charBase += 5;
            frame.y += 2;
        }
    }
    FreePointerIfSet_020ba294(&messages.file);
    func_ov027_020ba25c(&context->slotMessages, func_ov001_02073634(6), 0);
    func_ov027_020ba25c(&context->statusMessages, func_ov001_02073634(4), 0);
}
