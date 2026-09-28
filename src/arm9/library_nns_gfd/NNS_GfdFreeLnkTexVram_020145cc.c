#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef struct LnkVramBlock LnkVramBlock;

extern LnkVramBlock *data_0205a8e4;
extern LnkVramBlock *data_0205a8e8;
extern LnkVramBlock *data_0205a8ec;
extern BOOL NNSi_GfdFreeLnkVram_02014458(LnkVramBlock **freeList, LnkVramBlock **blockPool, u32 addr, u32 szByte);

int NNS_GfdFreeLnkTexVram_020145cc(NNSGfdTexKey texKey)
{
    const u32 addr = (texKey & 0xffff) << 3;
    const u32 szByte = ((texKey & 0x7fff0000) >> 16) << 4;
    const BOOL is4x4Comp = (texKey & 0x80000000) >> 31;

    if (szByte != 0) {
        BOOL result;
        if (is4x4Comp) {
            result = NNSi_GfdFreeLnkVram_02014458(&data_0205a8e8, &data_0205a8ec, addr, szByte);
        } else {
            result = NNSi_GfdFreeLnkVram_02014458(&data_0205a8e4, &data_0205a8ec, addr, szByte);
        }
        if (result) {
            return 0;
        } else {
            return 1;
        }
    }
    return 2;
}
