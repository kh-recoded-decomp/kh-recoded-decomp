#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

NNSSndArcLoadResult NNSi_SndArcLoadSeq(int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);
extern NNSSndArcLoadResult NNSi_SndArcLoadSeq (int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);

BOOL NNS_SndArcLoadSeq_0201f318 (int seqNo, NNSSndHeapHandle heap)
{
    NNSSndArcLoadResult result;

    result = NNSi_SndArcLoadSeq(seqNo, NNS_SND_ARC_LOAD_ALL, heap, TRUE, NULL);

    return result == NNS_SND_ARC_LOAD_SUCESS ? TRUE : FALSE;
}
