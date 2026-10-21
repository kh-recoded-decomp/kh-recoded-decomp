#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void Text_UploadTileBuffer(void *layer);

/* Sends the caption layer's tiles to VRAM unless it is hidden. */
void UploadStageCaptionLayer(StageCaption *caption)
{
    if (caption->hidden == FALSE) {
        Text_UploadTileBuffer(caption);
    }
}
