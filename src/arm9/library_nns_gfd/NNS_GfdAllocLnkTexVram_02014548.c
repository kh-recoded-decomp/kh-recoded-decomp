#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct LnkVramBlock LnkVramBlock;

extern LnkVramBlock *data_0205a8e4;
extern LnkVramBlock *data_0205a8e8;
extern LnkVramBlock *data_0205a8ec;
extern BOOL NNSi_GfdAllocLnkVram_02014288(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 *outAddr,
                                          u32 szByte);

static inline u32 RoundUpTexSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_TEXSIZE_MIN;
    } else {
        return (size + 0xf) & ~0xf;
    }
}

static inline NNSGfdTexKey MakeTexKey(u32 addr, u32 szByte, BOOL is4x4Comp)
{
    return ((szByte >> 4) << 16) | ((addr >> 3) & 0xffff) | (is4x4Comp << 31);
}

NNSGfdTexKey NNS_GfdAllocLnkTexVram_02014548(u32 szByte, BOOL is4x4Comp, u32 option)
{
    u32 addr;
    BOOL success;

    szByte = RoundUpTexSize(szByte);
    if (szByte >= NNS_GFD_TEXSIZE_MAX) {
        return NNS_GFD_ALLOC_ERROR_TEXKEY;
    }

    if (is4x4Comp) {
        success = NNSi_GfdAllocLnkVram_02014288(&data_0205a8e8, &data_0205a8ec, &addr, szByte);
    } else {
        success = NNSi_GfdAllocLnkVram_02014288(&data_0205a8e4, &data_0205a8ec, &addr, szByte);
    }

    if (success) {
        return MakeTexKey(addr, szByte, is4x4Comp);
    } else {
        return NNS_GFD_ALLOC_ERROR_TEXKEY;
    }
}
