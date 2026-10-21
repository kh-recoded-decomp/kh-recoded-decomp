#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void ClearStageCaptionLayer(StageCaption *caption);
extern StageHudEntry *GetHudEntry(int id);
extern void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);

/* Lays the requested HUD entries out as the caption's queued lines (one column of ten characters each). */
void QueueStageCaptionLines(StageCaption *caption)
{
    int i;
    StageHudEntry *entry;

    ClearStageCaptionLayer(caption);
    for (i = 0; i < caption->unk50; i++) {
        StageTextLine *line = &caption->queued[i];

        entry = GetHudEntry(caption->lines[i].messageId);
        SetStageCaptionLine(caption, line, entry->messageId, entry->rows, 1, FALSE);
        DrawStageCaptionLine(caption, line, 2);
    }
    UploadStageCaptionLayer(caption);
    caption->queuedCount = caption->unk50;
}
