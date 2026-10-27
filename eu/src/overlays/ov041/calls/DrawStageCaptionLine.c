#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern const StageCaptionFrameTiles gStageCaptionFrameTiles;
extern const u16 gStageCaptionTextFormat[];
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern const u16 *func_ov027_020ba2c8(void *messages, int index);
extern u16 *func_ov027_020ba300(void *messages, int index, u16 *buffer, int capacity, ...);
extern s32 GetHudLabelId(int labelIndex);
extern int OS_SNPrintf_0202e094(u16 *buffer, int capacity, const u16 *format, ...);
extern int GetTextLayerLineWidth(void *layer, const u16 *text, const u16 **nextLine);
extern void *GetFieldFont1(void);
extern void *GetSceneFont(void);
extern void Obj_SetField14(void *layer, void *font);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);

/* Draws a caption line: its frame, two rows of tiles in the given style, then (unless the style is 4) its text
 * centred in it. Style 0 shows the line's message, style 2 message 0xd with the line's label and count, any other
 * style the label alone; text too wide for the frame is drawn in the smaller field font. */
void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int style)
{
    u16 text[0x40];
    StageCaptionFrameTiles tiles;
    int last;
    u8 *chars;
    u32 frame;
    int i;
    u8 *dst;
    u8 *cursor;
    int width;

    chars = caption->unpackedChars->pRawData;
    tiles = gStageCaptionFrameTiles;
    frame = tiles.offsets[style];
    last = line->width - 1;
    dst = caption->surface->chars + line->offset * 0x20;
    cursor = dst + 0x20;

    /* top row: left corner, right corner, then the edge in between */
    MIi_CpuCopyFast(chars + frame, dst, 0x20);
    MIi_CpuCopyFast(chars + frame + 0x60, dst + last * 0x20, 0x20);
    for (i = 0; i < line->width - 2; i++) {
        MIi_CpuCopyFast(chars + frame + 0x40, cursor, 0x20);
        cursor += 0x20;
    }

    /* bottom row, one tile row (30 tiles) further down */
    cursor = dst + 0x3e0;
    MIi_CpuCopyFast(chars + frame + 0x20, dst + 0x3c0, 0x20);
    MIi_CpuCopyFast(chars + frame + 0xa0, dst + 0x3c0 + last * 0x20, 0x20);
    for (i = 0; i < line->width - 2; i++) {
        MIi_CpuCopyFast(chars + frame + 0x80, cursor, 0x20);
        cursor += 0x20;
    }

    if (style == 4) {
        return;
    }
    switch (style) {
    case 0:
        OS_SNPrintf_0202e094(text, 0x40, gStageCaptionTextFormat, func_ov027_020ba2c8(&caption->messages, line->messageId));
        break;
    case 2:
        func_ov027_020ba300(&caption->messages, 0xd, text, 0x40, GetHudLabelId(line->messageId), line->rows);
        break;
    default:
        OS_SNPrintf_0202e094(text, 0x40, gStageCaptionTextFormat, GetHudLabelId(line->messageId));
        break;
    }
    width = GetTextLayerLineWidth(caption, text, 0);
    if (width >= line->width * 8 - 12) {
        Obj_SetField14(caption, GetFieldFont1());
        width = GetTextLayerLineWidth(caption, text, 0);
    }
    DrawTextAnchored(caption, line->offset * 8 + (line->width * 8 - width) / 2, 4, 2, 0x209, text);
    Obj_SetField14(caption, GetSceneFont());
}
