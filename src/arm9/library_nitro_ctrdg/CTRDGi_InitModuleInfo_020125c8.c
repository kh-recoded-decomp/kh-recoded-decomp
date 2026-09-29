#pragma opt_rotateloops off
#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/ctrdg.h"

#define REG_MI_EXMEMCNT (*(vu16 *)REG_EXMEMCNT_ADDR)
#define REG_OS_IME (*(vu16 *)REG_IME_ADDR)
#define REG_OS_PAUSE (*(vu16 *)REG_PAUSE_ADDR)
#define MODULE_INFO_BUF 0x02fffc30
#define SET_MODULE_INFO_ONCE 0x02ffff9a
#define IS_CTRDG_EXIST 0x02ffff9b

extern CTRDGWork data_0205a2a4;
extern BOOL data_0205a2a8;
extern CTRDGHeader data_0205a2e0;

extern OSIrqMask OS_SetIrqMask_02001f30(OSIrqMask mask);
extern void CTRDGi_LockByProcessor_02012464(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_UnlockByProcessor_020124a0(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_ChangeLatestAccessCycle_02012408(CTRDGRomCycle *cycle);
extern void CTRDGi_RestoreAccessCycle_0201243c(CTRDGRomCycle *cycle);
extern void CTRDGi_SendtoPxi_020124b8(u32 data);
extern void DC_InvalidateRange_02003414(void *start, u32 size);
extern void DC_FlushAll_020033e0(void);
extern void StartHalfwordDmaTransferChecked_02004f6c(int dmaNo, u32 src, u32 dest, u32 size, int mode);
extern void MIi_CpuCopy32_01ff8710(const void *src, void *dest, u32 size);
extern BOOL CTRDG_IsExisting_02012364(void);
extern void WaitByLoop(s32 count);

static inline void SetMainMemoryPriority(MIProcessor proc)
{
    REG_MI_EXMEMCNT = (u16)((REG_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_EP_MASK) | (proc << REG_MI_EXMEMCNT_EP_SHIFT));
}

static inline MIProcessor GetMainMemoryPriority(void)
{
    return (MIProcessor)((REG_MI_EXMEMCNT & REG_MI_EXMEMCNT_EP_MASK) >> REG_MI_EXMEMCNT_EP_SHIFT);
}

static inline BOOL EnableIrq(void)
{
    u16 previous = REG_OS_IME;
    REG_OS_IME = 1;
    return (BOOL)previous;
}

static inline BOOL RestoreIrq(BOOL enable)
{
    u16 previous = REG_OS_IME;
    REG_OS_IME = (u16)enable;
    return (BOOL)previous;
}

void CTRDGi_InitModuleInfo_020125c8(void)
{
    CTRDGLockByProc lockInfo;
    OSIrqMask lastIE;
    BOOL lastIME;

    if (data_0205a2a8) {
        return;
    }
    data_0205a2a8 = TRUE;

    if (!(REG_OS_PAUSE & REG_OS_PAUSE_CHK_MASK)) {
        return;
    }

    lastIE = OS_SetIrqMask_02001f30(OS_IE_SPFIFO_RECV);
    lastIME = EnableIrq();

    CTRDGi_LockByProcessor_02012464(data_0205a2a4.lockID, &lockInfo);
    {
        MIProcessor proc = GetMainMemoryPriority();
        CTRDGRomCycle cycle;

        CTRDGi_ChangeLatestAccessCycle_02012408(&cycle);
        SetMainMemoryPriority(MI_PROCESSOR_ARM9);

        DC_InvalidateRange_02003414(&((u8 *)&data_0205a2e0)[0x80], sizeof(CTRDGHeader) - 0x80);
        StartHalfwordDmaTransferChecked_02004f6c(1, HW_CTRDG_ROM + 0x80, (u32)&((u8 *)&data_0205a2e0)[0x80],
                                                 sizeof(CTRDGHeader) - 0x80, 1);

        SetMainMemoryPriority(proc);
        CTRDGi_RestoreAccessCycle_0201243c(&cycle);
    }
    CTRDGi_UnlockByProcessor_020124a0(data_0205a2a4.lockID, &lockInfo);

    if (*(u8 *)IS_CTRDG_EXIST || !*(u8 *)SET_MODULE_INFO_ONCE) {
        int i;
        CTRDGHeader *header = &data_0205a2e0;
        CTRDGModuleInfo *info = (CTRDGModuleInfo *)MODULE_INFO_BUF;

        info->moduleID.raw = header->moduleID;
        for (i = 0; i < 3; i++) {
            info->exLsiID[i] = header->exLsiID[i];
        }
        info->makerCode = header->makerCode;
        info->gameCode = header->gameCode;

        *(u8 *)IS_CTRDG_EXIST = (u8)(CTRDG_IsExisting_02012364() ? 1 : 0);
        *(u8 *)SET_MODULE_INFO_ONCE = TRUE;
    }

    MIi_CpuCopy32_01ff8710((void *)CTRDG_SYSROM9_NINLOGO_ADR, data_0205a2e0.nintendoLogo,
                           sizeof(data_0205a2e0.nintendoLogo));
    DC_FlushAll_020033e0();

    CTRDGi_SendtoPxi_020124b8(CTRDG_PXI_COMMAND_INIT_MODULE_INFO
                              | (((u32)&data_0205a2e0 - HW_MAIN_MEM) >> 5) << CTRDG_PXI_COMMAND_PARAM_SHIFT);

    while (data_0205a2a4.subpInitialized != TRUE) {
        WaitByLoop(1);
    }

    (void)RestoreIrq(lastIME);
    (void)OS_SetIrqMask_02001f30(lastIE);
}
