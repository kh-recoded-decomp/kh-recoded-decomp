#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *font;
    int hSpace;
    int vSpace;
    u8 pad_20[0x14];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk_08;
    u16 palette;
} TextFrame;

typedef struct {
    int state;
    u32 flags;
    int frameCount;
    u8 pad_0c[0xc];
    TextLayer textLayer;
    const u16 *text;
    TextFrame frame;
} PopupState;

typedef struct {
    u8 pad_00[8];
    void *font;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern u32 func_ov093_020c3bb8(PopupState *popup, u32 mask);
extern void func_ov093_020c3b94(PopupState *popup, u32 mask);
extern BOOL InitTextLayerAt_020014b0(TextLayer *layer, int layerIndex, u16 *screenBase, void *font, TextFrame *frame);
extern int G2D_MeasureTextWidth_02016bc0(void *font, int hSpace, const void *text);
extern int NNSi_G2dFontGetTextHeight_02016b4c(void *font, int vSpace, const void *text);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawTextColored_02001668(TextLayer *layer, int x, int y, int color, int altColor, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void FillBackgroundLayerRect_02001a60(TextLayer *layer, void *dst, int x, int y, u8 palette);

void DrawPopupText_020c2e04(PopupState *popup)
{
    TextFrame *frame;
    int width;
    int height;
    int x;
    int y;

    if (func_ov093_020c3bb8(popup, 1) != 0) {
        return;
    }
    frame = &popup->frame;
    InitTextLayerAt_020014b0(&popup->textLayer, 6, NULL, g_popupManager_020c50e4->font, frame);
    width = G2D_MeasureTextWidth_02016bc0(popup->textLayer.font, popup->textLayer.hSpace, popup->text);
    height = NNSi_G2dFontGetTextHeight_02016b4c(popup->textLayer.font, popup->textLayer.vSpace, popup->text);
    x = frame->width * 8 / 2 - width / 2;
    y = frame->height * 8 / 2 - height / 2 - 1;
    CallVirtualHandlerSlot1_02001574(&popup->textLayer, 6);
    DrawTextColored_02001668(&popup->textLayer, x, y, 2, 7, popup->text);
    FlushBufferAndRunCallback_0200153c(&popup->textLayer);
    FillBackgroundLayerRect_02001a60(&popup->textLayer, G2S_GetBG2ScrPtr_02006f0c(), popup->frame.x, frame->y, frame->palette);
    func_ov093_020c3b94(popup, 1);
}
