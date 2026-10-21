#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* Forgets every line laid out on the caption layer. */
void ResetStageCaptionLines(StageCaption *caption)
{
    caption->charOffset = 0;
    caption->unk54 = 0;
    caption->unk50 = 0;
    caption->unk48 = 0;
}
