#ifndef KH_RECODED_FONT_RESOURCES_H
#define KH_RECODED_FONT_RESOURCES_H

#include "nnsys/g2d.h"

typedef struct FontResource {
    NNSG2dFont font;
    void *fileBuffer;
} FontResource;

/* Partial native layer prefix. This is not the full layer allocation size. */
typedef struct TextLayerFontView {
    NNSG2dFont *defaultFont;
    u8 reserved04[0x0c];
    NNSG2dTextCanvas canvas;
} TextLayerFontView;

typedef char FontResourceNativeSize[sizeof(FontResource) == 12 ? 1 : -1];
typedef char FontFileBufferOffset[(u32)&((FontResource *)0)->fileBuffer == 8 ? 1 : -1];
typedef char TextLayerCanvasFontOffset[(u32)&((TextLayerFontView *)0)->canvas.pFont == 0x14 ? 1 : -1];

BOOL LoadUtf16FontResource(FontResource *resource, const char *path);
void DrawTextAnchoredWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, u32 drawFlags, const u16 *text,
    NNSG2dFont *fallbackFont, s32 maxWidth);
void DrawTaggedTextWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, s32 alternateColor, const u16 *text,
    NNSG2dFont *fallbackFont, s32 maxWidth);

#endif
