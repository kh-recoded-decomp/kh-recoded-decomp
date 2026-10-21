#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/*
 * Brings the next queued line forward: lines before it shift left by its width (the one just before also by a
 * character), the new current one starts at character 1. Returns the queued lines still to come.
 */
int AdvanceQueuedCaptionLine(StageCaption *caption)
{
    int index = caption->lineCount;
    int width;
    int i;
    StageTextLine *line;

    if (index >= caption->queuedCount) {
        return 0;
    }
    width = caption->queued[index].width;
    caption->lineCount = index + 1;
    for (i = 0; i < caption->queuedCount; i++) {
        line = &caption->queued[i];
        if (i == caption->lineCount) {
            line->charBase = 1;
        } else if (i == caption->lineCount - 1) {
            line->charBase = line->charStart - width - 1;
        } else {
            line->charBase = line->charStart - width;
        }
    }
    return caption->queuedCount - caption->lineCount;
}
