#include "nitro/types.h"

typedef struct FontResource {
    u16 unk_00;
    u16 defaultGlyph;
} FontResource;

typedef struct Font {
    FontResource *resource;
} Font;

typedef struct GlyphWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} GlyphWidths;

typedef struct TextMetrics {
    u8 pad_00[4];
    Font *font;
    int spacing;
} TextMetrics;

extern u16 G2D_FindGlyphIndex_02016a10(Font *font, u16 code);
extern GlyphWidths *G2D_GetGlyphWidths_02016a58(Font *font, u16 glyph);

int MeasureTextLine_020cf17c(TextMetrics *metrics, const u16 *text, const u16 **next)
{
    Font *font = metrics->font;
    int spacing = metrics->spacing;
    int width = 0;
    u16 code;
    int result;

    while ((code = *text) != 0 && code != '\n' && code != 0x1f) {
        if (code >= 0x20) {
            u16 glyph = G2D_FindGlyphIndex_02016a10(font, code);
            if (glyph == 0xffff) {
                glyph = font->resource->defaultGlyph;
            }
            width += spacing + G2D_GetGlyphWidths_02016a58(font, glyph)->charWidth;
        }
        text++;
    }
    result = width - spacing;
    if (result <= 0) {
        result = 0;
    }
    if (next != NULL) {
        if (code == '\n') {
            *next = text + 1;
            return result;
        }
        *next = NULL;
    }
    return result;
}