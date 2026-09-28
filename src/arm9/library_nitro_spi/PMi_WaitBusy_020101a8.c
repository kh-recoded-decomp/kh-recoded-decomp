#include "nitro/types.h"

#define PM_BUSY_METHOD_PROC_MODE 2
#define PM_BUSY_METHOD_CPSR_IRQ 4
#define PM_BUSY_METHOD_IME 8

#define OS_PROCMODE_IRQ 0x12
#define OS_INTRMODE_IRQ_DISABLE 0x80

#define reg_OS_IME (*(vu16 *)0x04000208)

extern volatile BOOL data_020597ec;
extern u32 data_02055c44;

extern u32 OS_GetProcMode_0200499c(void);
extern u32 OS_GetCpsrIrq_02004990(void);
extern void PXIi_HandlerRecvFifoNotEmpty_0200e374(void);

void PMi_WaitBusy_020101a8(void)
{
    volatile BOOL *busy = &data_020597ec;

    while (*busy) {
        if (((data_02055c44 & PM_BUSY_METHOD_PROC_MODE) && OS_GetProcMode_0200499c() == OS_PROCMODE_IRQ)
            || ((data_02055c44 & PM_BUSY_METHOD_CPSR_IRQ) && OS_GetCpsrIrq_02004990() == OS_INTRMODE_IRQ_DISABLE)
            || ((data_02055c44 & PM_BUSY_METHOD_IME) && reg_OS_IME == 0)) {
            PXIi_HandlerRecvFifoNotEmpty_0200e374();
        }
    }
}
