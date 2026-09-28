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

WMErrCode WMi_StartMP_02011a70(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, WMMPTmpParam *tmpParam)
{
    WMErrCode result;
    WMArm9Buf *p = Ov105_GetContext();
    WMStatus *status = p->status;

    result = Ov105_WMi_CheckStateEx(2, WM_STATE_PARENT, WM_STATE_CHILD);
    WM_CHECK_RESULT(result);

    DC_InvalidateRange(&(status->aid), 2);
    DC_InvalidateRange(&(status->pwrMgtMode), 2);

    if (status->aid != 0 && status->pwrMgtMode != 1) {
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    DC_InvalidateRange(&(status->mp_flag), 4);

    if (status->mp_flag == TRUE) {
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    if ((recvBufSize & 0x3f) != 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    if ((sendBufSize & 0x1f) != 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    DC_InvalidateRange(&(status->mp_ignoreSizePrecheckMode), sizeof(status->mp_ignoreSizePrecheckMode));

    if (status->mp_ignoreSizePrecheckMode == FALSE) {
        if (recvBufSize < Ov105_WM_GetMPReceiveBufferSize()) {
            return WM_ERRCODE_INVALID_PARAM;
        }

        if (sendBufSize < Ov105_WM_GetMPSendBufferSize()) {
            return WM_ERRCODE_INVALID_PARAM;
        }
    }

    Ov105_SetCommandArg(WM_APIID_START_MP, callback);

    {
        WMStartMPReq Req;

        MI_CpuClear32(&Req, sizeof(Req));

        Req.apiid = WM_APIID_START_MP;
        Req.recvBuf = (u32 *)recvBuf;
        Req.recvBufSize = (u32)(recvBufSize / 2);
        Req.sendBuf = (u32 *)sendBuf;
        Req.sendBufSize = (u32)sendBufSize;

        MI_CpuClear32(&Req.param, sizeof(Req.param));
        MI_CpuCopy32(tmpParam, &Req.tmpParam, sizeof(Req.tmpParam));

        result = Ov105_WMi_SendCommandDirect(&Req, sizeof(Req));
        WM_CHECK_RESULT(result);
    }

    return WM_ERRCODE_OPERATING;
}
