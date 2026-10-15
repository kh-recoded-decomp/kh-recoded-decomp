#include "nitro/types.h"
#include "nnsys/g2d.h"

/* The legacy symbol handles text-color tags, not chooser selection. */
void SelectChooserValueByIndex(u16 tag, NNSG2dTagCallbackInfo *info)
{
    const u32 *colors = info->cbParam;

    if (tag <= 2) {
        int index = tag - 1;
        info->clr = (u8)colors[index];
    }
}
