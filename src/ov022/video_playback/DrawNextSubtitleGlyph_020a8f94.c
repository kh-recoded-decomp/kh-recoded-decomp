#include "nitro/types.h"

typedef struct SubtitleStream {
    u8 pad_00[0x34];
    s32 lineWidth;
    u8 pad_38[0x4];
    u16 marginLeft;
    u16 pad_3E;
    u16 marginTop;
    u8 pad_42[0x6];
    s32 lineHeight;
    s32 penX;
    s32 penY;
    s32 color;
    u8 pad_58[0x10];
    char *text;
    u8 pad_6C[0x10];
    s32 glyphSpacing;
} SubtitleStream;

typedef struct GlyphRef {
    s8 *glyph;
    s32 unk_04;
} GlyphRef;

extern u16 decodeMovieSubtitleCodeUnit_020a8b90(SubtitleStream *stream);
extern void MobiClip_ResolveGlyphRecord_02001a00(SubtitleStream *stream, GlyphRef *ref, int codeUnit);
extern int advanceMovieStreamWindow_020a8a78(SubtitleStream *stream);
extern char *strchr_020220f0(char *s, int c);
extern int func_020019f4(SubtitleStream *stream);
extern void CallVirtualHandler_02001a3c(SubtitleStream *stream, int x, int y, int color, GlyphRef *ref);

BOOL DrawNextSubtitleGlyph_020a8f94(SubtitleStream *stream)
{
    GlyphRef ref;
    int codeUnit;
    long advance;

    do {
        codeUnit = decodeMovieSubtitleCodeUnit_020a8b90(stream);
    } while (codeUnit == 1);

    if (codeUnit != 0) {
        int penY = stream->penY;
        MobiClip_ResolveGlyphRecord_02001a00(stream, &ref, codeUnit);
        advance = ref.glyph[2] + stream->glyphSpacing;
        if (stream->penX + advance > stream->lineWidth) {
            if (advanceMovieStreamWindow_020a8a78(stream) == 0) {
                return FALSE;
            }
        }
        if (strchr_020220f0(stream->text, '\n') == NULL) {
            penY += stream->lineHeight + func_020019f4(stream);
        }
        CallVirtualHandler_02001a3c(stream, stream->penX + stream->marginLeft + 1,
                                    penY + stream->marginTop + 1, 2, &ref);
        CallVirtualHandler_02001a3c(stream, stream->penX + stream->marginLeft,
                                    penY + stream->marginTop, stream->color, &ref);
        stream->penX += advance;
        return TRUE;
    }
    return FALSE;
}
