#include "nitro/types.h"
#include "nitro/os_types.h"

typedef struct {
    u16 aidBitmap;
    u16 receivedBitmap;
    u16 data[254];
} WMDataSet;

typedef struct {
    WMDataSet ds[4];
    u16 seqNum[4];
    u16 writeIndex;
    u16 sendIndex;
    u16 readIndex;
    u16 aidBitmap;
    u16 dataLength;
    u16 stationNumber;
    u16 dataSetLength;
    u16 port;
    u16 doubleMode;
} WMDataSharingInfo;

extern u16 *WmGetSharedDataAddress_02012250(WMDataSharingInfo *dsInfo, u32 aidBitmap, u16 *receiveBuf, u32 aid);
extern void MIi_CpuCopy16_01ff869c(const void *src, void *dest, u32 size);
extern void MIi_CpuClear16_01ff8684(u16 data, void *dest, u32 size);
extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);

void WmDataSharingReceiveData_020120cc(WMDataSharingInfo *dsInfo, u16 aid, u16 *data)
{
    u16 aidBit = (u16)(0x0001 << aid);

    if (dsInfo->aidBitmap & aidBit) {
        u16 *buf;
        u16 index;

        if (!(dsInfo->ds[dsInfo->writeIndex].aidBitmap & aidBit)) {
            if (dsInfo->doubleMode == TRUE) {
                index = (u16)((dsInfo->writeIndex + 1) % 4U);
                if (!(dsInfo->ds[index].aidBitmap & aidBit)) {
                    return;
                }
            } else {
                return;
            }
        } else {
            index = dsInfo->writeIndex;
        }

        buf = WmGetSharedDataAddress_02012250(dsInfo, dsInfo->aidBitmap, dsInfo->ds[index].data, aid);

        if (data != NULL) {
            MIi_CpuCopy16_01ff869c(data, buf, dsInfo->dataLength);
        } else {
            MIi_CpuClear16_01ff8684(0, buf, dsInfo->dataLength);
        }

        {
            OSIntrMode enabled = OS_DisableInterrupts_02004938();
            dsInfo->ds[index].aidBitmap &= ~aidBit;
            dsInfo->ds[index].receivedBitmap |= aidBit;
            (void)OS_RestoreInterrupts_0200494c(enabled);
        }
    }
}
