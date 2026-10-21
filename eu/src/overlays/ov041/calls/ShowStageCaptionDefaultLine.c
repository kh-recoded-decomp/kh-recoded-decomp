#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void SelectFieldMenuPage(int page);
extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, const void *text, int rows, int columns,
                                BOOL fixedStart);
extern void ClearStageCaptionLayer(StageCaption *caption);
extern void func_ov041_020ce4cc(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern void func_ov041_020ce77c(StageCaption *caption, StageTextLine *line, int palette);

/* Shows the caption's own line again (an empty, 30-character-wide line) on the first menu page. */
void ShowStageCaptionDefaultLine(StageCaption *caption)
{
    SelectFieldMenuPage(0);
    func_ov041_020ce40c(caption, &caption->line, NULL, 0, 3, FALSE);
    ClearStageCaptionLayer(caption);
    func_ov041_020ce4cc(caption, &caption->line, 0);
    UploadStageCaptionLayer(caption);
    func_ov041_020ce77c(caption, &caption->line, 9);
}
