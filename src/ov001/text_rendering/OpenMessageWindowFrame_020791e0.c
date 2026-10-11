#include "nitro/types.h"

typedef struct ModeContext {
    s32 mode;
    u8 pad_04[0xf0];
    s32 fadeLevel;
} ModeContext;

typedef struct TextSize {
    s32 width;
    s32 height;
} TextSize;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk08;
    u16 palette;
    u16 charBase;
    u16 unk0e;
} TextFrame;

typedef struct MessageWindow {
    u8 pad_00[0xc];
    s32 fixedSize;
    u8 pad_10[2];
    u16 top;
    u16 lineLimit;
    u16 rows;
    u16 pixelX;
    u16 pixelY;
    u8 pad_1c[0x78];
    u8 textLayer[4];
} MessageWindow;

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_WIN1H (*(vu16 *)0x04000042)
#define REG_WIN1V (*(vu16 *)0x04000046)
#define REG_WININ (*(vu16 *)0x04000048)
#define REG_WINOUT (*(vu16 *)0x0400004a)

extern ModeContext *data_ov001_020a04c4;
extern void *GetFieldFont3_020711e0(void);
extern int func_ov001_0207123c(void);
extern void *UpdateWidgetLayerDefault_020b9df0(int layer, int mode);
extern void func_ov027_020b9e00(int layer, int mode);
extern int MeasureMessageTiles_02078dd8(TextSize *size, BOOL useFixedSize, const void *font, const void *text);
extern int PlaceMessageWindow_02078ff8(MessageWindow *window, TextSize *size, TextFrame *rect, int extraWidth);
extern void G2x_SetBlendAlpha_02006850(void *reg, int plane1, int plane2, int ev1, int ev2);
extern void InitTextLayerAt_020014b0(void *layer, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void FlushBufferAndRunCallback_0200153c(void *layer);

static inline void SetWnd1InsidePlane(int wnd, BOOL effect)
{
    int value = (REG_WININ & ~0x3f00) | (wnd << 8);
    REG_WININ = (u16)(value | (effect << 13));
}

static inline void SetWndOutsidePlane(int wnd, BOOL effect)
{
    REG_WINOUT = (u16)((REG_WINOUT & ~0x3f) | ((u32)wnd | ((u32)effect << 5)));
}

static inline void SetWnd1Position(int x1, int y1, int x2, int y2)
{
    REG_WIN1H = (u16)(((x1 << 8) & 0xff00) | (x2 & 0xff));
    REG_WIN1V = (u16)(((y1 << 8) & 0xff00) | (y2 & 0xff));
}

void OpenMessageWindowFrame_020791e0(MessageWindow *window, const void *text)
{
    void *font = GetFieldFont3_020711e0();
    ModeContext *context = data_ov001_020a04c4;
    int layer = func_ov001_0207123c();
    void *screenBase = UpdateWidgetLayerDefault_020b9df0(layer, 10);
    TextSize size;
    TextFrame frame;
    int tiles;

    tiles = MeasureMessageTiles_02078dd8(&size, (context->mode == 2 && window->fixedSize == 0) ? 0x1e : window->fixedSize,
                                         font, text);
    if ((u32)(context->mode - 8) <= 1) {
        frame.width = size.width < 4 ? 4 : size.width;
    } else {
        frame.width = size.width < 2 ? 2 : size.width;
    }
    frame.height = size.height < 1 ? 1 : size.height;
    frame.unk08 = 1;
    frame.palette = 0xf;
    frame.charBase = 0;
    frame.unk0e = 3;
    window->lineLimit = frame.width + tiles + 2;
    if (PlaceMessageWindow_02078ff8(window, &size, &frame, tiles)) {
        window->pixelX = frame.x << 3;
        window->pixelY = frame.y << 3;
        SetWnd1InsidePlane(0xf, TRUE);
        SetWndOutsidePlane(0xf, FALSE);
        SetWnd1Position(window->pixelX, window->pixelY, window->pixelX + frame.width * 8,
                        window->pixelY + frame.height * 8);
        REG_DISPCNT &= ~0xe000;
        G2x_SetBlendAlpha_02006850((void *)0x04000050, 4, 1, 0x10, 0);
        context->fadeLevel = 0;
    }
    InitTextLayerAt_020014b0(window->textLayer, 2, screenBase, font, &frame);
    FlushBufferAndRunCallback_0200153c(window->textLayer);
    func_ov027_020b9e00(layer, 10);
    window->top = frame.y - 1;
    window->rows = frame.height + 2;
}
