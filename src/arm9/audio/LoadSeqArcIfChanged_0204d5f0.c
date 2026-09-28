#include "nitro/types.h"
#include "nnsys/snd.h"

extern u8 *g_soundWork_0206084c;
extern int func_0201f154(NNSSndHeapHandle heap);
extern void func_0201f1a4(NNSSndHeapHandle heap, int level);
extern void FSi_WaitForCardThread_01ff8140(void);
extern void SoundMgr_WaitLoaderIfState1_0204d6c0(void);
extern BOOL NNS_SndArcLoadSeq_0201f348(int seqNo, NNSSndHeapHandle heap);

void LoadSeqArcIfChanged_0204d5f0(int seqArcNo)
{
    u8 *base = g_soundWork_0206084c;
    int index;

    if (*(int *)(base + 0xa4) == seqArcNo) {
        func_0201f1a4(*(NNSSndHeapHandle *)(base + 0xb04b4), *(int *)(base + 0xa0));
    } else {
        *(int *)(base + 0xa4) = seqArcNo;
        FSi_WaitForCardThread_01ff8140();
        SoundMgr_WaitLoaderIfState1_0204d6c0();
        func_0201f1a4(*(NNSSndHeapHandle *)(base + 0xb04b4), *(int *)(base + 0xa8));
        NNS_SndArcLoadSeq_0201f348(seqArcNo, *(NNSSndHeapHandle *)(base + 0xb04b4));
        *(int *)(base + 0xa0) = func_0201f154(*(NNSSndHeapHandle *)(base + 0xb04b4));
    }

    for (index = 0; index < 3; index++) {
        *(int *)(base + index * 4 + 0xa8) = 0;
    }

    *(s16 *)(base + 0xb4736) = -1;
    *(u16 *)(base + 0xb4734) = 0;
}
