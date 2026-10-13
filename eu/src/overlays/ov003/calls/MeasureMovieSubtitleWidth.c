#include "nitro/types.h"

typedef struct {
    void *font;
    u8 reserved04[0x58 - 4];
    int cursor;
    int alternateCursor;
    int activeSource;
    u8 reserved64[4];
    const s8 *sources[5];
    int letterSpacing;
} SubtitleRenderer;
typedef struct { s8 left; u8 glyphWidth; s8 advance; } GlyphWidths;
typedef struct { const GlyphWidths *widths; const u8 *bitmap; } GlyphRecord;

extern int ClampMovieSubtitleStep(SubtitleRenderer *, int);
extern void MobiClip_ResolveGlyphRecord(SubtitleRenderer *, GlyphRecord *, u32);

/* Measure the widest subtitle line, including the four insertion sources.
 * Source cursors are local copies; a newline delegates to the next line.
 * The subtitle parser supplies source ids 0..4 and one- to three-byte UTF-8. */
int MeasureMovieSubtitleWidth(SubtitleRenderer *renderer)
{
    int mainCursor = renderer->cursor;
    int otherCursor;
    int firstSourceCursor = 0;
    int secondSourceCursor = 0;
    int activeSource = renderer->activeSource;
    int width = 0;
    u16 codepoint;
    const s8 *buffer;
    int *cursor;
    GlyphRecord glyph;

    for (;;) {
        int byte;
        const s8 *character;
        switch (activeSource) {
        case 0:
            buffer = renderer->sources[0];
            cursor = &mainCursor;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            buffer = renderer->sources[activeSource];
            cursor = &otherCursor;
            break;
        }
        character = buffer + *cursor;
        byte = *character;
        if (byte == 0) {
            if (activeSource == 0) return width;
            activeSource = 0;
            continue;
        }
        if (byte >= 1 && byte < 0x20) {
            switch (byte) {
            case 8:
                otherCursor = firstSourceCursor;
                activeSource = 1;
                break;
            case 9:
                otherCursor = secondSourceCursor;
                activeSource = 2;
                break;
            case 11:
                otherCursor = 0;
                activeSource = 3;
                break;
            case 12:
                otherCursor = 0;
                activeSource = 4;
                break;
            case 10:
                *cursor += 1;
                renderer->cursor = *cursor;
                return ClampMovieSubtitleStep(renderer, width);
            }
            *cursor += 1;
            continue;
        }
        if (byte >= 0x20 && byte < 0x80) {
            codepoint = (u16)byte;
            *cursor += 1;
        } else if ((byte & 0xe0) == 0xc0) {
            u16 low = (u16)(buffer[*cursor + 1] & 0x3f);
            u16 high = (u16)(byte & 0x1f);
            codepoint = (u16)((high << 6) | low);
            *cursor += 2;
        } else if ((byte & 0xf0) == 0xe0) {
            codepoint = (u16)(((u16)(buffer[*cursor + 1] & 0x3f) << 6) |
                ((u16)(byte & 0xf) << 12) | (u16)(buffer[*cursor + 2] & 0x3f));
            *cursor += 3;
        }
        MobiClip_ResolveGlyphRecord(renderer, &glyph, codepoint);
        width += glyph.widths->advance + renderer->letterSpacing;
    }
}
