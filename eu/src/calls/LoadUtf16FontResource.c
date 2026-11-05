#include "src/text/FontResources.h"

/* Only path/mode have a logical role in this native loader chain. */
extern void *Archive_LoadFile(const char *path, u32 mode);
extern void NNS_G2dFontInitUTF16(NNSG2dFont *font, void *fileBuffer);

BOOL LoadUtf16FontResource(FontResource *resource, const char *path)
{
    resource->fileBuffer = Archive_LoadFile(path, 0x0e);
    NNS_G2dFontInitUTF16(&resource->font, resource->fileBuffer);
    return TRUE;
}
