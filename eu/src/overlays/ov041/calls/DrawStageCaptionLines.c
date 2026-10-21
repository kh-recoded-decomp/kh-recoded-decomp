#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void MapStageCaptionLine(StageCaption *caption, StageTextLine *line, int palette);
extern void *func_ov001_0207123c(void);
extern void MarkTileTableRowDirty(void *table, int layer);

/* Puts several text lines on the caption's tile map and marks it for upload. */
void DrawStageCaptionLines(StageCaption *caption, StageTextLine *lines, int count, int palette)
{
    int i;

    for (i = 0; i < count; i++) {
        MapStageCaptionLine(caption, &lines[i], palette);
    }
    MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
}
