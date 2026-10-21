#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern const StageTextFrame gStageCaptionFrame;
extern void *GetSceneFont(void);
extern BOOL InitTextLayerAt(void *layer, int bgLayer, void *charBase, void *font, StageTextFrame *frame);
extern u32 MakePrimaryVramKey_02073634(u32 id);
extern void LoadPackedFileView(void **view, u32 fileId, BOOL compressed);

/* Sets the caption up: a 30x2 text window at (1, 1) on layer 3 with the scene font, and its message file. */
void InitStageCaption(StageCaption *caption)
{
    StageTextFrame frame = gStageCaptionFrame;

    InitTextLayerAt(caption, 3, NULL, GetSceneFont(), &frame);
    LoadPackedFileView(&caption->messages, MakePrimaryVramKey_02073634(1), TRUE);
}
