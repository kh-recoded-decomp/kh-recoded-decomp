#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, const void *text, int rows, int columns,
                                BOOL fixedStart);
extern void func_ov041_020ce4cc(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern void func_ov041_020ce77c(StageCaption *caption, StageTextLine *line, int palette);
extern void *func_ov001_0207123c(void);
extern void MarkTileTableRowDirty(void *table, int layer);
extern void SetStageCaptionState(StageCaption *caption, int state);

/* Shows a notice text (30 characters wide) on the caption and moves it to state 3. */
void ShowStageCaptionNotice(StageCaption *caption, const void *text)
{
    func_ov041_020ce40c(caption, &caption->notice, text, 0, 3, FALSE);
    func_ov041_020ce4cc(caption, &caption->notice, 3);
    UploadStageCaptionLayer(caption);
    func_ov041_020ce77c(caption, &caption->notice, 9);
    if (!caption->hidden) {
        MarkTileTableRowDirty(func_ov001_0207123c(), 0xb);
    }
    SetStageCaptionState(caption, 3);
}
