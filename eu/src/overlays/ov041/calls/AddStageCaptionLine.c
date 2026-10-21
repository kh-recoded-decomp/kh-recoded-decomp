#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* A HUD entry: its text and how many rows it takes. */
typedef struct StageHudEntry {
    u32 id;
    const void *text;
    int rows;
} StageHudEntry;

extern StageHudEntry *GetHudEntry(int id);
extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, const void *text, int rows, int columns,
                                BOOL fixedStart);
extern void func_ov041_020ce4cc(StageCaption *caption, StageTextLine *line, int arg);
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
    func_ov041_020ce40c(caption, line, (const void *)hudId, entry->rows, 1, TRUE);
    func_ov041_020ce4cc(caption, line, 1);
    UploadStageCaptionLayer(caption);
    caption->unk50 = ++caption->lineCount;
    return caption->unk50;
}
