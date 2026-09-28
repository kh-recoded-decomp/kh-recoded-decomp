#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/wm.h"

#define PXI_FIFO_TAG_WM         10
#define PXI_PROC_ARM7           1
#define MI_DMA_MAX_NUM          3

extern u16 data_ov105_020bfa20;
#define wmInitialized data_ov105_020bfa20
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

extern WMArm9Buf *Ov105_GetContext(void);
extern WMErrCode Ov105_IsDeviceReady(void);
extern WMErrCode Ov105_PollDeviceStatus(void);
extern WMErrCode Ov105_WMi_CheckStateEx(s32 paramNum, ...);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
extern WMErrCode Ov105_WMi_SendCommandDirect(void *data, u32 length);
extern void Ov105_SetCommandArg(WMApiid id, WMCallbackFunc callback);
extern int Ov105_WM_GetMPSendBufferSize(void);
extern int Ov105_WM_GetMPReceiveBufferSize(void);
extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *dst, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);
#define MI_CpuClear32(dst, size) INITi_CpuClear32_0x01ff86fc(0, (dst), (size))
#define MI_CpuCopy32(src, dst, size) MIi_CpuCopy32((src), (dst), (size))

extern WMErrCode Ov105_WMi_StartMP(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, WMMPTmpParam *tmpParam);

WMErrCode WM_StartMP_02011b6c(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, u16 mpFreq)
{
    WMMPTmpParam tmpParam;

    MI_CpuClear32(&tmpParam, sizeof(tmpParam));

    tmpParam.mask = WM_MP_TMP_PARAM_FREQUENCY | WM_MP_TMP_PARAM_MIN_FREQUENCY;
    tmpParam.minFrequency = mpFreq;
    tmpParam.frequency = mpFreq;

    return Ov105_WMi_StartMP(callback, recvBuf, recvBufSize, sendBuf, sendBufSize, &tmpParam);
}
