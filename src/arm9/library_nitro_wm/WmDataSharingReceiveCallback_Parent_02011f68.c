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
    u16 currentSeqNum;
    u16 state;
} WMDataSharingInfo;

typedef struct {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 *recvBuf;
    u16 *data;
    u16 length;
    u16 aid;
    u8 macAddress[6];
    u16 seqNo;
    void *arg;
} WMPortRecvCallback;

extern void WmDataSharingReceiveData_020120cc(WMDataSharingInfo *dsInfo, u16 aid, u16 *data);
extern BOOL WmDataSharingSendDataSet_0201215c(WMDataSharingInfo *dsInfo, BOOL delegate);
extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);

void WmDataSharingReceiveCallback_Parent_02011f68(void *arg) {
    WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;
    WMDataSharingInfo *dsInfo = (WMDataSharingInfo *)cb->arg;

    if (dsInfo) {
        if (cb->errcode == 0) {
            switch (cb->state) {
            case 21:
                WmDataSharingReceiveData_020120cc(dsInfo, cb->aid, cb->data);
                (void)WmDataSharingSendDataSet_0201215c(dsInfo, FALSE);
                break;
            case 7:
                (void)WmDataSharingSendDataSet_0201215c(dsInfo, FALSE);
                break;
            case 25:
                break;
            case 9:
            case 26:
                {
                    OSIntrMode enabled;
                    u32 aidBit = 1U << cb->aid;
                    u16 writeIndex;

                    enabled = OS_DisableInterrupts_02004938();
                    writeIndex = dsInfo->writeIndex;
                    dsInfo->ds[writeIndex].aidBitmap &= ~aidBit;
                    if (dsInfo->doubleMode == TRUE) {
                        dsInfo->ds[(u16)((writeIndex + 1) % 4U)].aidBitmap &= ~aidBit;
                    }
                    (void)OS_RestoreInterrupts_0200494c(enabled);
                    (void)WmDataSharingSendDataSet_0201215c(dsInfo, FALSE);
                    if (dsInfo->doubleMode == TRUE) {
                        (void)WmDataSharingSendDataSet_0201215c(dsInfo, FALSE);
                    }
                }
                break;
            }
        } else {
            dsInfo->state = 5;
        }
    }
}
