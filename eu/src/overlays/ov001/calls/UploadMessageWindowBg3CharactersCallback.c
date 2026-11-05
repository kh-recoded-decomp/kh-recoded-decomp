#include "nitro/types.h"
#include "src/overlays/ov027/FileLoadQueue.h"

extern void GX_LoadBG3Char(u32 arg1, u32 arg2, u32 arg3);
extern void NNS_G2dGetUnpackedBGCharacterData(u32 tag, s32 *out);

void UploadMessageWindowBg3CharactersCallback(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 tag;
    s32 resource;
    u32 unused;

    unused = unused3;
    tag = (u32)GetFileLoadRequestBuffer((const FileLoadRequest *)entry);
    NNS_G2dGetUnpackedBGCharacterData(tag, &resource);
    GX_LoadBG3Char(*(u32 *)(resource + 0x14), 0x800, *(u32 *)(resource + 0x10));
    DestroyFileLoadRequest((FileLoadRequest *)entry, TRUE);
}
