#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void ClearStageCaptionRows(void);
extern void ShowStageCaptionDefaultLine(StageCaption *caption);
extern void SetStageCaptionState(StageCaption *caption, int state);
extern void *func_ov001_0207123c(void);
extern void MarkTileTableRowDirty(void *table, int layer);

/* Clears the caption and starts over: state 1 with its default line, or state 4 when lines are waiting. */
int ClearStageCaption(StageCaption *caption)
{
    caption->lineCount = 0;
    caption->charOffset = 0;
    ClearStageCaptionRows();
    if (caption->unk50 == 0) {
        ShowStageCaptionDefaultLine(caption);
        SetStageCaptionState(caption, 1);
    } else {
        SetStageCaptionState(caption, 4);
        caption->unk4c = 0;
    }
    MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
    return caption->queuedCount;
}
