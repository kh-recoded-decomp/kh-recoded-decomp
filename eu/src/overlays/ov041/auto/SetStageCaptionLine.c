#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/*
 * Lays a text line out on the caption layer: its characters go after the ones already placed (or at 0 when
 * it has its own), it is columns * 10 characters wide and at most 5 rows high.
 */
void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                         BOOL fixedStart)
{
    int offset;

    if (line->fixedStart != 0) {
        offset = 0;
    } else {
        offset = caption->charOffset / 8;
    }
    line->messageId = messageId;
    line->charStart = fixedStart ? 0x20 : offset + 1;
    line->charBase = offset + 1;
    line->width = columns * 10;
    line->rows = rows > 5 ? 5 : rows;
    line->offset = offset;
    caption->charOffset += line->width * 8;
}
