#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct LnkVramBlock LnkVramBlock;

extern LnkVramBlock *data_0205a900;
extern LnkVramBlock *data_0205a904;
extern BOOL NNSi_GfdAllocLnkVramAligned_0201429c(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 *outAddr,
                                                 u32 szByte, u32 alignment);
extern BOOL NNSi_GfdFreeLnkVram_02014458(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 addr, u32 szByte);

static inline u32 RoundUpPlttSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_PLTTSIZE_MIN;
    } else {
        return (size + 7) & ~7;
    }
}

static inline NNSGfdPlttKey MakePlttKey(u32 addr, u32 szByte)
{
    return ((szByte >> 3) << 16) | ((addr >> 3) & 0xffff);
}

NNSGfdPlttKey NNS_GfdAllocLnkPlttVram_020148ac(u32 szByte, BOOL is4Pltt, u32 option)
{
    u32 addr;
    BOOL success;

    szByte = RoundUpPlttSize(szByte);
    if (szByte >= NNS_GFD_PLTTSIZE_MAX) {
        return NNS_GFD_ALLOC_ERROR_PLTTKEY;
    }

    if (is4Pltt) {
        success = NNSi_GfdAllocLnkVramAligned_0201429c(&data_0205a900, &data_0205a904, &addr, szByte, 8);
        if (addr + szByte > NNS_GFD_4PLTT_MAX_ADDR) {
            NNSi_GfdFreeLnkVram_02014458(&data_0205a900, &data_0205a904, addr, szByte);
            return NNS_GFD_ALLOC_ERROR_PLTTKEY;
        }
    } else {
        success = NNSi_GfdAllocLnkVramAligned_0201429c(&data_0205a900, &data_0205a904, &addr, szByte, 16);
    }

    if (success) {
        return MakePlttKey(addr, szByte);
    } else {
        return NNS_GFD_ALLOC_ERROR_PLTTKEY;
    }
}
