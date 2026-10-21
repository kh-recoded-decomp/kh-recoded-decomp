#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern void MapStageCaptionLine(StageCaption *caption, StageTextLine *line, int palette);
extern void *func_ov001_0207123c(void);
extern void MarkTileTableRowDirty(void *table, int layer);
extern void SetStageCaptionState(StageCaption *caption, int state);

/* Shows a notice text (30 characters wide) on the caption and moves it to state 3. */
void ShowStageCaptionNotice(StageCaption *caption, u32 messageId)
{
    SetStageCaptionLine(caption, &caption->notice, messageId, 0, 3, FALSE);
    DrawStageCaptionLine(caption, &caption->notice, 3);
    UploadStageCaptionLayer(caption);
    MapStageCaptionLine(caption, &caption->notice, 9);
    if (!caption->hidden) {
        MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
    }
    SetStageCaptionState(caption, 3);
}
