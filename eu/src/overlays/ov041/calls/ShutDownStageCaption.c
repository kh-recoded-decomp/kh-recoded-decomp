#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void DestroyStageCaption(StageCaption *caption);
extern void FreeStageCaptionChars(StageCaption *caption);

/* Takes the caption down and frees everything it loaded. */
void ShutDownStageCaption(StageCaption *caption)
{
    DestroyStageCaption(caption);
    FreeStageCaptionChars(caption);
}
