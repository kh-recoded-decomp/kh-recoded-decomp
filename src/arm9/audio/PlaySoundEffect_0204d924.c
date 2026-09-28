#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00000[0xa4];
    int defaultSeqArcNo;
    u8 pad_000a8[0xb44dc - 0xa8];
    NNSSndHandle seHandle;
} SoundWork;

extern SoundWork *g_soundWork_0206084c;
extern BOOL func_0201fd7c(NNSSndHandle *handle, int seqArcNo, int index);

BOOL PlaySoundEffect_0204d924(int seqArcNo, int index)
{
    if (seqArcNo == 0) {
        seqArcNo = g_soundWork_0206084c->defaultSeqArcNo;
    }
    return func_0201fd7c(&g_soundWork_0206084c->seHandle, seqArcNo, index);
}
