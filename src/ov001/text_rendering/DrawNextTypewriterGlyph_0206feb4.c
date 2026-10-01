#include "nitro/types.h"

typedef struct {
    u8 data[0x38];
} TextSurface;

typedef struct {
    u8 pad_00[0x34];
    TextSurface surface;
    const u16 *cursor;
    u8 pad_70[4];
    int penX;
} TextWriter;

extern int ForwardInnerPayload_020018e4(TextSurface *surface, int x, int y, int color, u16 glyph);
extern void Text_UploadTileBuffer_02001520(TextSurface *surface);

BOOL DrawNextTypewriterGlyph_0206feb4(TextWriter *writer) {
    if (*writer->cursor == 0) {
        return FALSE;
    }
    writer->penX += ForwardInnerPayload_020018e4(&writer->surface, writer->penX, 3, 2, *writer->cursor);
    Text_UploadTileBuffer_02001520(&writer->surface);
    writer->cursor++;
    return TRUE;
}
