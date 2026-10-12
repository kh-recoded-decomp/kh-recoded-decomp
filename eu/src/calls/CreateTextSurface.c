#include "nitro/types.h"

typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const void *vtable;
} NNSG2dCharCanvas;

typedef struct TextSurface {
    struct TextSurface *prev;
    struct TextSurface *next;
    u32 reserved08;
    NNSG2dCharCanvas canvas;
    void *chars;
} TextSurface;

typedef struct TextSurfaceList {
    TextSurface *head;
    TextSurface *tail;
    u16 count;
    u16 linkOffset;
} TextSurfaceList;

typedef struct TextLayer {
    u32 reserved00;
    TextSurfaceList surfaces;
    NNSG2dCharCanvas *canvas;
    u8 reserved14[0xc];
    TextSurface *selected;
    u32 reserved24;
    u32 charBytes;
    u16 reserved2c;
    u16 areaWidth;
    u16 areaHeight;
    u8 charSize;
    u8 flags;
} TextLayer;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dest, u8 value, u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void NNS_G2dCharCanvasInitForOBJ1D(NNSG2dCharCanvas *canvas, void *chars, int width, int height, int bpp);
extern void NNS_G2dCharCanvasInitForBG(NNSG2dCharCanvas *canvas, void *chars, int width, int height, int bpp);
extern void NNS_FndAppendListObject(TextSurfaceList *list, TextSurface *surface);
extern void SelectListNodeOrFirst(TextLayer *layer, TextSurface *surface);

TextSurface *CreateTextSurface(TextLayer *layer, BOOL select, BOOL fromEnd)
{
    TextSurface *surface;
    void *chars;
    if (fromEnd) {
        surface = NNS_FndAllocFromDefaultExpHeapEx(sizeof(TextSurface), -4);
        MI_CpuFill8(surface, 0, sizeof(TextSurface));
        chars = NNS_FndAllocFromDefaultExpHeapEx(layer->charBytes, -4);
        surface->chars = chars;
        MIi_CpuClearFast(0, chars, layer->charBytes);
    } else {
        surface = NNSi_FndAllocFromDefaultHeap(sizeof(TextSurface));
        MI_CpuFill8(surface, 0, sizeof(TextSurface));
        chars = NNS_FndAllocFromDefaultExpHeapEx(layer->charBytes, 4);
        surface->chars = chars;
        MIi_CpuClearFast(0, chars, layer->charBytes);
    }
    if (layer->flags & 0x80) {
        NNS_G2dCharCanvasInitForOBJ1D(&surface->canvas, surface->chars, layer->areaWidth, layer->areaHeight, 4);
    } else {
        NNS_G2dCharCanvasInitForBG(&surface->canvas, surface->chars, layer->areaWidth, layer->areaHeight, layer->charSize == 32 ? 4 : 8);
    }
    NNS_FndAppendListObject(&layer->surfaces, surface);
    if (select) {
        SelectListNodeOrFirst(layer, surface);
    }
    return surface;
}
