#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern StageHudEntry *GetHudEntry(int id);
extern void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);

/* In state 0, lays a HUD entry out as the next caption line (at most three); returns the lines shown. */
int AddStageCaptionLine(StageCaption *caption, int hudId)
{
    StageHudEntry *entry = GetHudEntry(hudId);
    StageTextLine *line;

    if (caption->state != 0) {
        return caption->unk50;
    }
    if (caption->lineCount >= 3) {
        return caption->unk50;
    }
    line = &caption->lines[caption->lineCount];
    SetStageCaptionLine(caption, line, hudId, entry->rows, 1, TRUE);
    DrawStageCaptionLine(caption, line, 1);
    UploadStageCaptionLayer(caption);
    caption->unk50 = ++caption->lineCount;
    return caption->unk50;
}
