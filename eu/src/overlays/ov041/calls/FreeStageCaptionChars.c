#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees the caption's character data. */
void FreeStageCaptionChars(StageCaption *caption)
{
    NNSi_FndFreeFromDefaultHeap(caption->charData);
}
