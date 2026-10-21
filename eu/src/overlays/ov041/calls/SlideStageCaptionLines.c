#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void *func_ov001_0207123c(void);
extern void ClearTileTableRect(void *table, int layer, int x, int y, int width, int height);
extern void MarkTileTableRowDirty(void *table, int layer);
extern void func_ov041_020ce77c(StageCaption *caption, StageTextLine *line, int palette);

/* Slides lines three characters further toward their place and redraws them; TRUE once all are in place. */
BOOL SlideStageCaptionLines(StageCaption *caption, StageTextLine *lines, int count)
{
    int i;
    BOOL done = TRUE;
    StageTextLine *line;

    if (!caption->hidden && count > 0) {
        ClearTileTableRect(func_ov001_0207123c(), 0xb, 0, 1, 0x20, 2);
    }
    for (i = 0; i < count; i++) {
        line = &lines[i];
        if (line->charBase < line->charStart) {
            line->charStart -= 3;
            if (line->charStart < line->charBase) {
                line->charStart = line->charBase;
            }
        }
        if (line->charStart != line->charBase) {
            done = FALSE;
        }
        func_ov041_020ce77c(caption, line, 9);
    }
    if (!caption->hidden && count > 0) {
        MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
    }
    return done;
}
