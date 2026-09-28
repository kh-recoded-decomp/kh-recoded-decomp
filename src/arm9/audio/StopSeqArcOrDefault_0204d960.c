#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern void func_0201d53c(int seqArcNo);

void StopSeqArcOrDefault_0204d960(int seqArcNo)
{
    if (seqArcNo == 0) {
        seqArcNo = *(int *)(g_soundWork_0206084c + 0xa4);
    }
    func_0201d53c(seqArcNo);
}
