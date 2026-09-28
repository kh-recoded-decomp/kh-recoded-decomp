#include "nitro/types.h"
#include "nitro/os.h"

extern int func_02004938(void);
extern void func_0200494c(int state);
extern unsigned int OS_ResetRequestIrqMask(unsigned int mask);
extern void OS_SetIrqFunction_02001d90(unsigned int intrBits, OSIrqFunction function);
extern unsigned int OS_EnableIrqMask(unsigned int mask);
extern void PXIi_HandlerRecvFifoNotEmpty_0200e374(void);
extern u16 data_02057b88;
extern void *data_02057b8c[32];

void PXI_InitFifo_0200e1f4(void)
{
    volatile u16 *sync = (volatile u16 *)0x04000180;
    int *shared = (int *)0x02fffc00;
    int state;
    int i;
    int timeout;
    int mark;
    int count;

    state = func_02004938();
    if (data_02057b88 == 0) {
        data_02057b88 = 1;
        shared[0xe2] = 0;
        for (i = 0; i < 0x20; i++) {
            data_02057b8c[i] = 0;
        }
        *(volatile u16 *)0x04000184 = 0xc408;
        OS_ResetRequestIrqMask(0x40000);
        OS_SetIrqFunction_02001d90(0x40000, (OSIrqFunction)&PXIi_HandlerRecvFifoNotEmpty_0200e374);
        OS_EnableIrqMask(0x40000);
        count = 0;
        for (;;) {
            mark = *sync & 0xf;
            *sync = (u16)(mark << 8);
            if (mark == 0 && count > 4) {
                break;
            }
            timeout = 1000;
            while ((*sync & 0xf) == mark) {
                if (timeout <= 0) {
                    count = 0;
                    break;
                }
                timeout--;
            }
            count++;
        }
    }
    func_0200494c(state);
}
