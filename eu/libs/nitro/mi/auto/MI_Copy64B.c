#include "nitro/types.h"

/* r0 holds the source address until the final four-word group. */
register u32 sSourceAddressOrWord __asm("r0");
register u32 *sCopyDestination __asm("r1");

register u32 sFirstScratchWord __asm("r2");
register u32 sSecondScratchWord __asm("r3");
register u32 sThirdScratchWord __asm("r12");

static __forceinline void CopyThreeWords(void)
{
    const u32 *source = (const u32 *)sSourceAddressOrWord;
    sFirstScratchWord = source[0];
    sSecondScratchWord = source[1];
    sThirdScratchWord = source[2];
    sSourceAddressOrWord += 3 * sizeof(u32);
    sCopyDestination[0] = sFirstScratchWord;
    sCopyDestination[1] = sSecondScratchWord;
    sCopyDestination[2] = sThirdScratchWord;
    sCopyDestination += 3;
}

/* Both buffers must be word-aligned and contain at least 64 bytes. */
void MI_Copy64B(const void *source, void *destination)
{
    sSourceAddressOrWord = (u32)source;
    sCopyDestination = destination;
    CopyThreeWords();
    CopyThreeWords();
    CopyThreeWords();
    CopyThreeWords();

    const u32 *lastGroup = (const u32 *)sSourceAddressOrWord;
    sFirstScratchWord = lastGroup[1];
    sSecondScratchWord = lastGroup[2];
    sThirdScratchWord = lastGroup[3];
    sSourceAddressOrWord = lastGroup[0];
    sCopyDestination[0] = sSourceAddressOrWord;
    sCopyDestination[1] = sFirstScratchWord;
    sCopyDestination[2] = sSecondScratchWord;
    sCopyDestination[3] = sThirdScratchWord;
    sCopyDestination += 4;
}
