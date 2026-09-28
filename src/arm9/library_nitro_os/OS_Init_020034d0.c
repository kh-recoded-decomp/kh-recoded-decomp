#include "nitro/types.h"
#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define SDK_ARM9
#define SDK_EXCEPTION_BUG

void OS_InitThread(void);
void OS_InitIrqTable(void);
extern void OSi_InitStackChecker(void);
void OS_InitLock(void);
void OSi_InstallExceptionVector(void);
void OS_InitArena(void);
void OS_InitArenaEx(void);
void OS_InitTick(void);
void OS_InitAlarm(void);
void OS_InitVAlarm(void);
void OS_InitReset(void);
void OSi_InitVramExclusive(void);
void PXI_Init(void);
void CARD_Init(void);
void MI_Init(void);
void PM_Init(void);
void CTRDG_Init(void);
extern void OSi_CancelDma0 (void);

void OS_Init_020034d0 (void)
{
#ifdef SDK_ARM9
#ifdef SDK_ENABLE_ARM7_PRINT
    OS_InitPrintServer();
#endif
    OS_InitArena();

    PXI_Init();

    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    OSi_InitStackChecker();
    OSi_InstallExceptionVector();

    MI_Init();

    OS_InitVAlarm();
    OSi_InitVramExclusive();

#ifndef SDK_NO_THREAD
    OS_InitThread();
#endif

#ifndef SDK_SMALL_BUILD
    OS_InitReset();
#endif

#ifndef SDK_TEG
    CTRDG_Init();
#endif

#ifndef SDK_SMALL_BUILD
    CARD_Init();
#endif

#ifndef SDK_TEG
    PM_Init();
#endif

    OSi_CancelDma0();

#else
    OS_InitArena();
    PXI_Init();
    OS_InitLock();
    OS_InitIrqTable();

#define SDK_EXCEPTION_BUG
#ifndef SDK_EXCEPTION_BUG
    OSi_InstallExceptionVector();
#endif
    OS_InitTick();
    OS_InitAlarm();
    OS_InitThread();

#ifndef SDK_SMALL_BUILD
    OS_InitReset();
#endif

#ifndef SDK_TEG
    CTRDG_Init();
#endif

#endif
}
