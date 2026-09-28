#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern struct {
    BOOL enableFlag;
    CTRDGWork work;
} data_0205a2a0;

extern int OS_DisableInterrupts_02004938(void);
extern void OS_RestoreInterrupts_0200494c(int state);
extern BOOL CTRDGi_HasValidModuleInfo_02012320(void);
extern u32 OS_SetDPermissionsForProtectionRegion_02003bb0(u32 mask, u32 access);
extern void DC_FlushAll_020033e0(void);
extern void DC_WaitWriteBufferEmpty_02003470(void);
extern void OS_EnableICacheForProtectionRegion_02003b70(u32 regions);
extern void OS_DisableICacheForProtectionRegion_02003b80(u32 regions);
extern void OS_EnableDCacheForProtectionRegion_02003b90(u32 regions);
extern void OS_DisableDCacheForProtectionRegion_02003ba0(u32 regions);
extern void OS_EnableWriteBufferForProtectionRegion_02003bc4(u32 regions);
extern void OS_DisableWriteBufferForProtectionRegion_02003bd4(u32 regions);

void CTRDG_Enable_020124e8(BOOL enable) {
    int state = OS_DisableInterrupts_02004938();

    data_0205a2a0.enableFlag = enable;

    if (CTRDGi_HasValidModuleInfo_02012320()) {
        u32 access = enable ? (1 << 12) : (5 << 12);
        OS_SetDPermissionsForProtectionRegion_02003bb0(0xf << 12, access);
        if (enable) {
            DC_FlushAll_020033e0();
            DC_WaitWriteBufferEmpty_02003470();
            OS_DisableICacheForProtectionRegion_02003b80(8);
            OS_DisableDCacheForProtectionRegion_02003ba0(8);
            OS_DisableWriteBufferForProtectionRegion_02003bd4(8);
        } else {
            OS_EnableICacheForProtectionRegion_02003b70(8);
            OS_EnableDCacheForProtectionRegion_02003b90(8);
            OS_EnableWriteBufferForProtectionRegion_02003bc4(8);
        }
    }

    OS_RestoreInterrupts_0200494c(state);
}
