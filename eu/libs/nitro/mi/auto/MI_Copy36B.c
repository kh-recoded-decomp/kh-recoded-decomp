#include "nitro/types.h"

/* These caller-clobbered cursor bindings apply only to this leaf's file. */
register const u32 *sCopySource __asm("r0");
register u32 *sCopyDestination __asm("r1");

static __forceinline void CopyThreeWords(void)
{
    u32 firstWord = sCopySource[0];
    u32 secondWord = sCopySource[1];
    u32 thirdWord = sCopySource[2];
    sCopySource += 3;
    sCopyDestination[0] = firstWord;
    sCopyDestination[1] = secondWord;
    sCopyDestination[2] = thirdWord;
    sCopyDestination += 3;
}

/* Both buffers must be word-aligned and contain at least 36 bytes. */
void MI_Copy36B(const void *source, void *destination)
{
    sCopySource = source;
    sCopyDestination = destination;
    CopyThreeWords();
    CopyThreeWords();
    CopyThreeWords();
}
