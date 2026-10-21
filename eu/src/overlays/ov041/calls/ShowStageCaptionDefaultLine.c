#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void SelectFieldMenuPage(int page);
extern void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void ClearStageCaptionLayer(StageCaption *caption);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern void MapStageCaptionLine(StageCaption *caption, StageTextLine *line, int palette);

/* Shows the caption's own line again (an empty, 30-character-wide line) on the first menu page. */
void ShowStageCaptionDefaultLine(StageCaption *caption)
{
    SelectFieldMenuPage(0);
    SetStageCaptionLine(caption, &caption->line, 0, 0, 3, FALSE);
    ClearStageCaptionLayer(caption);
    DrawStageCaptionLine(caption, &caption->line, 0);
    UploadStageCaptionLayer(caption);
    MapStageCaptionLine(caption, &caption->line, 9);
}
