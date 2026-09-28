#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);
extern u16 OS_ReadOwnerOfLockWord_02002398(void *lockWord);
extern s32 OS_TryLockCartridge_020022e0(u16 lockID);
extern void WaitByLoop(s32 count);

void CTRDGi_LockByProcessor_02012464(u16 lockID, CTRDGLockByProc *info)
{
    while (1) {
        info->irq = OS_DisableInterrupts_02004938();
        if (((info->locked = OS_ReadOwnerOfLockWord_02002398((void *)0x02ffffe8) & 0x40) != 0)
            || (OS_TryLockCartridge_020022e0(lockID) == 0)) {
            break;
        }
        OS_RestoreInterrupts_0200494c(info->irq);
        WaitByLoop(1);
    }
}
