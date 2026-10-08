#include "nitro/types.h"

#define REG_BLDCNT (*(volatile u16 *)0x04000050)

extern unsigned int data_ov045_020c08a0;
extern unsigned int sOv045_UiBtlGwP2_020c0834;
extern unsigned int sOv045_UiBtlBtluiP2_020c0844;
extern unsigned int MI_CpuFill8();
extern unsigned int MI_CpuCopy8();
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int SetMenuGaugeActive();
extern unsigned int func_ov001_02075248();
extern unsigned int OpenMessageContainer();
extern void func_ov045_020be730(void);

unsigned int InitBattleGaugeContext(unsigned int arguments)
{
    u16 *work;
    unsigned int scene;
    u8 *layout;
    unsigned int mode;

    work = (u16 *)NNSi_FndGetCurrentRootHeap();
    mode = 0;
    MI_CpuFill8(work, 0, 0x1a4c);
    MI_CpuCopy8(arguments, work, 0x10);
    data_ov045_020c08a0 = (u32)work;
    scene = func_ov001_02075248(0);
    *(unsigned int *)(work + 0x10) = scene;
    SetMenuGaugeActive(0, 0);
    if (*work == 3) {
        layout = (u8 *)&sOv045_UiBtlGwP2_020c0834;
    } else {
        layout = (u8 *)&sOv045_UiBtlBtluiP2_020c0844;
        mode = 2;
    }
    OpenMessageContainer(work + 0x12, work + 0x16, layout, mode);
    REG_BLDCNT = 0;
    return (u32)func_ov045_020be730;
}
