#include "nitro/types.h"

typedef struct TextLayer TextLayer;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charOffset;
    u16 palette;
    u16 color;
    u16 spacing;
} TextFrame;

typedef struct {
    u8 pad_00[0x23a94];
    u8 font[0x10];
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern BOOL InitTextLayerAt_020014b0(TextLayer *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *obj, int arg);
extern void Text_UploadTileBuffer_02001520(TextLayer *obj);

void InitScrollTextLayer_02063988(TextLayer *obj, int height, u16 *screenBase, int bgId)
{
    TextFrame frame;
    int layer = 0;

    switch (bgId) {
    case 5:
        layer = 1;
        break;
    case 0x15:
        layer = 5;
        break;
    }
    frame.x = 9;
    frame.y = 0;
    frame.charOffset = 0;
    frame.width = 23;
    frame.height = height;
    frame.palette = 15;
    frame.color = 0;
    frame.spacing = 6;
    InitTextLayerAt_020014b0(obj, layer, screenBase, g_scrollText_020645a0.work->font, &frame);
    CallVirtualHandlerSlot1_02001574(obj, 0);
    Text_UploadTileBuffer_02001520(obj);
}
