#include "src/overlays/ov038/Ov038SoundContext.h"

u32 GetOv038ResumeFlags(void)
{
    return gOv038SoundContext->flags & 0x20;
}
