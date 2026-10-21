#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* The next queued line to lay out (in out), or NULL when there is none left. */
StageCaptionLineRef *GetQueuedCaptionLine(StageCaption *caption, StageCaptionLineRef *out)
{
    StageTextLine *line = &caption->queued[caption->lineCount];

    if (caption->lineCount >= caption->queuedCount) {
        return NULL;
    }
    out->messageId = line->messageId;
    out->rows = line->rows;
    return out;
}
