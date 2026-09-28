#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x810];
    u16 dataLength;
} WMDataSharingInfo;

extern u32 func_0200d594(u32 bits);

u16 *WmGetSharedDataAddress_02012250(WMDataSharingInfo *dsInfo, u32 aidBitmap, u16 *receiveBuf, u32 aid)
{
    u32 mask;
    u32 count;
    u32 offset;

    mask = (0x0001 << aid) - 1;
    aidBitmap &= mask;
    count = func_0200d594(aidBitmap);
    offset = dsInfo->dataLength * count;

    return (u16 *)(((u8 *)receiveBuf) + offset);
}
