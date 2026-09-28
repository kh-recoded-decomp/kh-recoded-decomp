#include "nitro/types.h"

typedef void (*MIDmaCallback)(void *arg);

extern u32 data_02055c1c;

extern void MIi_DmaFill32Async_02005014(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback,
                                        void *arg, BOOL dmaEnable);
extern void StartWordDmaTransfer_02004e44(int dmaNo, u32 dest, u32 src, u32 size, int mode);
extern void func_01ff86fc(u32 data, void *dest, u32 size);

void G3X_InitTable_02006c30(void)
{
    int i;

    if (data_02055c1c != (u32)-1) {
        MIi_DmaFill32Async_02005014(data_02055c1c, (void *)0x04000330, 0, 0x10, NULL, NULL, TRUE);
        StartWordDmaTransfer_02004e44(data_02055c1c, 0x04000360, 0, 0x60, 1);
    } else {
        func_01ff86fc(0, (void *)0x04000330, 0x10);
        func_01ff86fc(0, (void *)0x04000360, 0x60);
    }

    for (i = 0; i < 32; i++) {
        *(vu32 *)0x040004d0 = 0;
    }
}
