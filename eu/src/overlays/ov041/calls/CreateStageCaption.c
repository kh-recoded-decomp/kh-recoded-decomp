#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern BOOL HasPendingSceneValue(void);
extern void InitStageCaption(StageCaption *caption);
extern void LoadStageCaptionChars(StageCaption *caption);

/* Starts the caption from scratch (hidden while a scene value is pending). */
void CreateStageCaption(StageCaption *caption)
{
    MI_CpuFill8(caption, 0, sizeof(StageCaption));
    caption->line.fixedStart = TRUE;
    caption->notice.fixedStart = TRUE;
    caption->hidden = HasPendingSceneValue();
    InitStageCaption(caption);
    LoadStageCaptionChars(caption);
}
