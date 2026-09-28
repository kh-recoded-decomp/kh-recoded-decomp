#include "nitro/os_types.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void OSi_RescheduleThread(void);

void OS_RescheduleThread_02002bb4(void)
{
    OSIntrMode nLast = OS_DisableInterrupts();

    OSi_RescheduleThread();
    OS_RestoreInterrupts(nLast);
}
