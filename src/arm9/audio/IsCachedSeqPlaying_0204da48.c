#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *g_soundWork_0206084c;
extern int func_0201d828(NNSSndHandle *handle);
extern int func_0201d6d8(int seqNo);

BOOL IsCachedSeqPlaying_0204da48(void)
{
    int seqNo = func_0201d828((NNSSndHandle *)(g_soundWork_0206084c + 0xb44d8));

    if (seqNo < 0) {
        goto notPlaying;
    }
    if (func_0201d6d8(seqNo) != 0) {
        goto isPlaying;
    }
notPlaying:
    return FALSE;
isPlaying:
    return TRUE;
}
