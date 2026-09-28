#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

inline REGType16v * GetBGnCNT (NNSG2dBGSelect n)
{
    extern REGType16v * const data_020530d4[];
    return data_020530d4[n];
}
inline BOOL IsMainBG (NNSG2dBGSelect bg)
{
    return (bg <= NNS_G2D_BGSELECT_MAIN3);
}
inline u16 MakeBGnCNTValAffine (GXBGScrSizeAffine screenSize, GXBGAreaOver areaOver, GXBGScrBase screenBase, GXBGCharBase charBase)
{
    return (u16)(
        (screenSize << 14 )
        | (screenBase << 8 )
        | (charBase << 2 )
        | (areaOver << 13 )
        );
}
inline void SetBGnControlAffine (NNSG2dBGSelect n, GXBGScrSizeAffine screenSize, GXBGAreaOver areaOver, GXBGScrBase screenBase, GXBGCharBase charBase)
{
    *GetBGnCNT(n) = (u16)(
        (*GetBGnCNT(n) & (0x0003 | 0x0040 ))
        | MakeBGnCNTValAffine(screenSize, areaOver, screenBase, charBase)
        );
}
extern const u8 data_02052fec[2][8];
extern void ChangeBGModeByTableMain (const u8 modeTable[]);
extern void ChangeBGModeByTableSub (const u8 modeTable[]);

void SetBGnControlToAffine_02015fe0 (NNSG2dBGSelect n, GXBGScrSizeAffine size, GXBGAreaOver areaOver, GXBGScrBase scnBase, GXBGCharBase chrBase)
{
    if (IsMainBG(n)) {
        ChangeBGModeByTableMain(data_02052fec[n - 2]);
    } else {
        ChangeBGModeByTableSub(data_02052fec[n - 6]);
    }
    SetBGnControlAffine(n, size, areaOver, scnBase, chrBase);
}
