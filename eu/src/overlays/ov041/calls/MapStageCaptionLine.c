#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern u16 *UpdateFieldWidgetLayer(int layer);

/* Puts a text line's characters in rows 1 and 2 of the caption's tile map with the given palette; columns
 * outside the 32-tile map are skipped. */
void MapStageCaptionLine(StageCaption *caption, StageTextLine *line, int palette)
{
    u16 *map = UpdateFieldWidgetLayer(0xb);
    int firstTile;
    int rowIndex;
    int x;
    int width;
    int tile;
    u16 *row;

    if (caption->hidden) {
        return;
    }
    firstTile = caption->tileBase + line->offset;
    tile = firstTile;
    width = line->width;
    row = map + 0x20;
    for (rowIndex = 0; rowIndex < 2; rowIndex++) {
        for (x = line->charStart; x < line->charStart + width; x++) {
            if (x < 0 || x > 0x1f) {
                tile++;
            } else {
                row[x] = tile | (palette << 12);
                tile++;
            }
        }
        tile = firstTile + 30;
        row += 0x20;
    }
}
