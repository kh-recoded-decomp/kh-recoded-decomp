#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern u32 MakePrimaryVramKey(u32 id);
extern void *func_0202c4a0(u32 key, int kind);
extern s32 NNS_G2dGetUnpackedBGCharacterData(void *resource, void **outPayload);

/* Loads the caption's character data (resource 0xd) and unpacks it. */
void LoadStageCaptionChars(StageCaption *caption)
{
    caption->charData = func_0202c4a0(MakePrimaryVramKey(0xd), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(caption->charData, &caption->unpackedChars);
}
