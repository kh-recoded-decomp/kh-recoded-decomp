#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk_08;
    u16 palette;
} TextFrame;

typedef struct {
    s32 state;
    s32 kind;
    u8 pad_08[0x24];
    s32 layer;
    u8 pad_30[0xC];
    u8 textLayer[0x34];
    const u16 *message;
    TextFrame frame;
} TextWindow;

typedef struct {
    u8 pad_00[0x644C];
    NNSG2dFont font;
} SceneResources;

extern SceneResources *data_ov036_020c3844;
extern BOOL IsPackedBitSet_020c27a0(void *base, int bitIndex);
extern BOOL InitTextLayerAt_020014b0(void *layer, int bg, u16 *screenBase, NNSG2dFont *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern NNSG2dTextRect G2D_MeasureTextRectangle_02016c18(const NNSG2dFont *font, int hSpace, int vSpace, const void *text);
extern void DrawTextPackedColor_0200174c(void *layer, int x, int y, int color, int flags, int highColor, const u16 *text);
extern void func_02001768(void *layer, int x, int y, int color, int flags, int highColor, const u16 *text, int unk);
extern void *G2_GetBG2ScrPtr_02006e88(void);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern int func_ov036_020c27bc(void *window, int *node);

static inline NNSG2dTextRect GetFontTextRect(const NNSG2dFont *font, int hSpace, int vSpace, const u16 *text)
{
    return G2D_MeasureTextRectangle_02016c18(font, hSpace, vSpace, text);
}

static inline NNSG2dTextRect MeasureMessage(const u16 *text)
{
    return GetFontTextRect(&data_ov036_020c3844->font, 0, 2, text);
}

void DrawTextWindow_020bebcc(TextWindow *window)
{
    TextFrame *frame = &window->frame;
    u16 *screen;

    if (IsPackedBitSet_020c27a0(window, 0)) {
        return;
    }
    InitTextLayerAt_020014b0(window->textLayer, window->layer, NULL, &data_ov036_020c3844->font, frame);
    switch (window->state) {
    case 0:
    case 4:
        switch (window->kind) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 15:
            CallVirtualHandlerSlot1_02001574(window->textLayer, 12);
            break;
        case 14:
            CallVirtualHandlerSlot1_02001574(window->textLayer, 0);
            break;
        default:
            CallVirtualHandlerSlot1_02001574(window->textLayer, 1);
            break;
        }
        break;
    case 1:
        CallVirtualHandlerSlot1_02001574(window->textLayer, 1);
        DrawTextAnchored_020015a0(window->textLayer, 0x11, 2, 2, 0x209, window->message);
        DrawTextAnchored_020015a0(window->textLayer, 0x10, 1, 3, 0x209, window->message);
        break;
    case 2: {
        NNSG2dTextRect rect;
        CallVirtualHandlerSlot1_02001574(window->textLayer, 8);
        rect = MeasureMessage(window->message);
        DrawTextPackedColor_0200174c(window->textLayer, (window->frame.width * 8) / 2 - rect.width / 2,
                                     (window->frame.height * 8) / 2 - rect.height / 2, 9, 0xF, 0xB,
                                     window->message);
        break;
    }
    case 3:
        CallVirtualHandlerSlot1_02001574(window->textLayer, 8);
        func_02001768(window->textLayer, 0, 0, 9, 7, 7, window->message, 0);
        break;
    }
    if (window->layer == 2) {
        screen = G2_GetBG2ScrPtr_02006e88();
    } else {
        screen = G2_GetBG3ScrPtr_02006f80();
    }
    FlushBufferAndRunCallback_0200153c(window->textLayer);
    FillBackgroundLayerRect_02001a60(window->textLayer, screen, frame->x, frame->y, frame->palette);
    func_ov036_020c27bc(window, NULL);
}
