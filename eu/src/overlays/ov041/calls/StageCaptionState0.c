#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void *func_ov001_0207123c(void);
extern void ClearTileTableRect(void *table, int layer, int x, int y, int width, int height);
extern void MarkTileTableRowDirty(void *table, int layer);
extern void MapStageCaptionLine(StageCaption *caption, StageTextLine *line, int palette);

/* Caption state 0: slides the laid-out lines three characters further toward their place and redraws them. */
void StageCaptionState0(StageCaption *caption)
{
    int i;
    StageTextLine *line;

    if (!caption->hidden) {
        ClearTileTableRect(func_ov001_0207123c(), 0xb, 0, 1, 0x20, 2);
    }
    for (i = 0; i < caption->lineCount; i++) {
        line = &caption->lines[i];
        if (line->charBase < line->charStart) {
            line->charStart -= 3;
            if (line->charStart < line->charBase) {
                line->charStart = line->charBase;
            }
        }
        MapStageCaptionLine(caption, line, 9);
    }
    if (!caption->hidden && caption->lineCount > 0) {
        MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
    }
}
