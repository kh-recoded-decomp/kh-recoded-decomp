#include "nitro/types.h"

typedef struct {
    u16 savedDispMode;
    u16 vramLockId;
} GXDisplayState;

typedef struct {
    u16 dispOnFlag;
    u16 pad_02;
    u32 dmaNo;
} GXDmaState;

extern volatile GXDisplayState data_02056f08;
extern GXDmaState data_02055c18;

extern void GX_InitGXState_02008f90(void);
extern s32 func_020023a0(void);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern void StartWordDmaTransfer_02004e44(int dmaNo, u32 dest, u32 src, u32 size, int mode);
extern void func_01ff86fc(u32 data, void *dest, u32 size);

void GX_Init_02006488(void)
{
    s32 lockId;

    *(vu16 *)0x04000304 |= 0x8000;
    *(vu16 *)0x04000304 = (u16)((*(vu16 *)0x04000304 & ~0x20e) | 0x20e);
    *(vu16 *)0x04000304 = (u16)(*(vu16 *)0x04000304 | 1);

    GX_InitGXState_02008f90();

    while (data_02056f08.vramLockId == 0) {
        lockId = func_020023a0();
        if (lockId == -3) {
            RunResetCallbackAndIdle_02004cf0();
        }
        data_02056f08.vramLockId = (u16)lockId;
    }

    *(vu16 *)0x04000004 = 0;
    *(vu32 *)0x04000000 = 0;

    if (data_02055c18.dmaNo != (u32)-1) {
        StartWordDmaTransfer_02004e44(data_02055c18.dmaNo, 0x04000008, 0, 0x60, 1);
        *(vu16 *)0x0400006c = 0;
        StartWordDmaTransfer_02004e44(data_02055c18.dmaNo, 0x04001000, 0, 0x70, 1);
    } else {
        func_01ff86fc(0, (void *)0x04000008, 0x60);
        *(vu16 *)0x0400006c = 0;
        func_01ff86fc(0, (void *)0x04001000, 0x70);
    }

    *(vu16 *)0x04000020 = 0x100;
    *(vu16 *)0x04000026 = 0x100;
    *(vu16 *)0x04000030 = 0x100;
    *(vu16 *)0x04000036 = 0x100;
    *(vu16 *)0x04001020 = 0x100;
    *(vu16 *)0x04001026 = 0x100;
    *(vu16 *)0x04001030 = 0x100;
    *(vu16 *)0x04001036 = 0x100;
}
