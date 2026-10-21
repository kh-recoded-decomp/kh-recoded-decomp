#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void DrawStageCaptionLines(StageCaption *caption, StageTextLine *lines, int count, int palette);
extern void Text_UploadTileBuffer(void *layer);

/* Draws again whatever the caption's state shows, and uploads it. */
void RedrawStageCaption(StageCaption *caption)
{
    switch (caption->state) {
    case 0:
        DrawStageCaptionLines(caption, caption->lines, caption->unk50, 9);
        break;
    case 1:
        DrawStageCaptionLines(caption, &caption->line, 1, 9);
        break;
    case 2:
        DrawStageCaptionLines(caption, caption->queued, caption->queuedCount, 1);
        break;
    case 3:
        DrawStageCaptionLines(caption, &caption->notice, 1, 1);
        break;
    default:
        return;
    }
    Text_UploadTileBuffer(caption);
}
