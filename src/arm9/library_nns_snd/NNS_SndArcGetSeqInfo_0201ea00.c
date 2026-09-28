#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct {
    u8 pad_00[0x98];
    NNSSndArcInfo *info;
} SndArcHandle;

extern SndArcHandle *data_0205e2e4;

static inline const void *GetPtrConst(const void *base, u32 offset)
{
    if (offset == 0) return NULL;
    return (const u8 *)base + offset;
}

static inline const NNSSndArcOffsetTable *GetOffsetTable(const NNSSndArcInfo *info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}

const NNSSndArcSeqInfo *NNS_SndArcGetSeqInfo_0201ea00(int seqNo)
{
    SndArcHandle *arc = data_0205e2e4;
    const NNSSndArcOffsetTable *table = GetOffsetTable(arc->info, arc->info->seqOffset);

    if (table == NULL) return NULL;
    if (seqNo < 0) return NULL;
    if ((u32)seqNo >= table->count) return NULL;

    return (const NNSSndArcSeqInfo *)GetPtrConst(arc->info, table->offset[seqNo]);
}
