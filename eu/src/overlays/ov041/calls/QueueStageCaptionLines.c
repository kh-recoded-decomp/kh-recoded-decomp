#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* A HUD entry: its text and how many rows it takes. */
typedef struct StageHudEntry {
    u32 id;
    const void *text;
    int rows;
} StageHudEntry;

extern void ClearStageCaptionLayer(StageCaption *caption);
extern StageHudEntry *GetHudEntry(int id);
extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, const void *text, int rows, int columns,
                                BOOL fixedStart);
extern void func_ov041_020ce4cc(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);

/* Lays the requested HUD entries out as the caption's queued lines (one column of ten characters each). */
void QueueStageCaptionLines(StageCaption *caption)
{
    int i;
    StageHudEntry *entry;

    ClearStageCaptionLayer(caption);
    for (i = 0; i < caption->unk50; i++) {
        StageTextLine *line = &caption->queued[i];

        entry = GetHudEntry(caption->lines[i].hudId);
        func_ov041_020ce40c(caption, line, entry->text, entry->rows, 1, FALSE);
        func_ov041_020ce4cc(caption, line, 2);
    }
    UploadStageCaptionLayer(caption);
    caption->queuedCount = caption->unk50;
}
