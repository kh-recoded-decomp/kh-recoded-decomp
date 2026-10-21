#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void ClearStageCaptionLayer(StageCaption *caption);
extern StageHudEntry *GetHudEntry(int id);
extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern BOOL CombineStageCaptionLines(StageCaption *caption, int index, BOOL checkOnly);

/* Queues the requested lines with the first two, or else the last two, merged into one combined entry; FALSE
 * when no pair combines. */
BOOL QueueCombinedCaptionPair(StageCaption *caption)
{
    BOOL combined = FALSE;
    StageHudEntry *entry;

    if (caption->unk50 < 2) {
        return FALSE;
    }
    ClearStageCaptionLayer(caption);
    if (CombineStageCaptionLines(caption, 0, FALSE)) {
        caption->queuedCount = 1;
        if (caption->unk50 == 3) {
            entry = GetHudEntry(caption->lines[2].messageId);
            func_ov041_020ce40c(caption, &caption->queued[1], entry->messageId, entry->rows, 1, FALSE);
            DrawStageCaptionLine(caption, &caption->queued[1], 2);
            caption->queuedCount++;
        }
        UploadStageCaptionLayer(caption);
        return TRUE;
    }
    if (caption->unk50 == 2) {
        return FALSE;
    }
    if (CombineStageCaptionLines(caption, 1, TRUE)) {
        entry = GetHudEntry(caption->lines[0].messageId);
        func_ov041_020ce40c(caption, &caption->queued[0], entry->messageId, entry->rows, 1, FALSE);
        DrawStageCaptionLine(caption, &caption->queued[0], 2);
        UploadStageCaptionLayer(caption);
        CombineStageCaptionLines(caption, 1, FALSE);
        caption->queuedCount = 2;
        combined = TRUE;
    }
    return combined;
}
