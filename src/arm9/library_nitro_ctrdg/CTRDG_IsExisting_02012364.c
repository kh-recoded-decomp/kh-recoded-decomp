#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern struct {
    BOOL enableFlag;
    CTRDGWork work;
} data_0205a2a0;


extern BOOL CTRDGi_HasValidModuleInfo_02012320(void);
extern void CTRDGi_LockByProcessor_02012464(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_UnlockByProcessor_020124a0(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_ChangeLatestAccessCycle_02012408(CTRDGRomCycle *r);
extern void CTRDGi_RestoreAccessCycle_0201243c(CTRDGRomCycle *r);

BOOL CTRDG_IsExisting_02012364(void)
{
    BOOL retval = TRUE;
    CTRDGLockByProc lockInfo;

    CTRDGHeader *chp = (CTRDGHeader *)0x08000000;
    CTRDGModuleInfo *cip = (CTRDGModuleInfo *)0x02fffc30;

    if (!CTRDGi_HasValidModuleInfo_02012320()) {
        return FALSE;
    }

    if (cip->detectPullOut == TRUE) {
        return FALSE;
    }
    CTRDGi_LockByProcessor_02012464(data_0205a2a0.work.lockID, &lockInfo);

    {
        CTRDGRomCycle rc;
        u8 isRomCode;

        CTRDGi_ChangeLatestAccessCycle_02012408(&rc);
        isRomCode = chp->isRomCode;

        if ((isRomCode == CTRDG_IS_ROM_CODE && cip->moduleID.raw != chp->moduleID)
            || (isRomCode != CTRDG_IS_ROM_CODE && cip->moduleID.raw != *(u16 *)0x0801fffe)
            || ((cip->gameCode != chp->gameCode) && cip->isAgbCartridge)) {
            cip->detectPullOut = TRUE;
            retval = FALSE;
        }

        CTRDGi_RestoreAccessCycle_0201243c(&rc);
    }

    CTRDGi_UnlockByProcessor_020124a0(data_0205a2a0.work.lockID, &lockInfo);
    return retval;
}
