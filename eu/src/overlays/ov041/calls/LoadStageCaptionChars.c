#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern u32 MakePrimaryVramKey(u32 id);
extern void *LoadFileAllocFromHeapTail(u32 key, int kind);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *resource, NNSG2dCharacterData **outData);

/* Loads the caption's character data (resource 0xd) and unpacks it. */
void LoadStageCaptionChars(StageCaption *caption)
{
    caption->charData = LoadFileAllocFromHeapTail(MakePrimaryVramKey(0xd), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(caption->charData, &caption->unpackedChars);
}
