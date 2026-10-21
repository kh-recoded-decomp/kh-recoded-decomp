#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void CallVirtualHandlerSlot1(void *object, int arg);

/* Clears the caption layer unless it is hidden. */
void ClearStageCaptionLayer(StageCaption *caption)
{
    if (caption->hidden == FALSE) {
        CallVirtualHandlerSlot1(caption, 0);
    }
}
