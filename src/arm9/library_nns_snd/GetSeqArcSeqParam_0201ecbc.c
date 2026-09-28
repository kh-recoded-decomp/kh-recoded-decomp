#include "nitro/types.h"

typedef struct {
    u32 fileId;
} NNSSndArcSeqArcInfo;

extern const NNSSndArcSeqArcInfo *NNS_SndArcGetSeqArcInfo_0201ea64(int seqArcNo);
extern void *NNS_SndArcGetFileAddress_0201ee28(u32 fileId);
extern u32 func_02021874(const void *seqArc);

u32 GetSeqArcSeqParam_0201ecbc(int seqArcNo)
{
    const NNSSndArcSeqArcInfo *seqArcInfo;
    void *seqArc;

    seqArcInfo = NNS_SndArcGetSeqArcInfo_0201ea64(seqArcNo);
    if (seqArcInfo == NULL) return 0;

    seqArc = NNS_SndArcGetFileAddress_0201ee28(seqArcInfo->fileId);
    if (seqArc == NULL) return 0;

    return func_02021874(seqArc);
}
