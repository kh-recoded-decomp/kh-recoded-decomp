#include "nitro/types.h"

extern u32 data_ov001_020a04f0;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dest, s32 value, u32 size);
extern void LoadBg2CharAndFrames(void *context);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopy16(void *dest, void *src, u32 size);
extern void UpdateBlinkPanel(void);

u32 func_ov001_0207dc68(u8 *param)
{
    u8 *context;

    context = NNSi_FndGetCurrentRootHeap();
    data_ov001_020a04f0 = (u32)context;
    MI_CpuFill8(context, 0, 0x4c);
    LoadBg2CharAndFrames(context);
    *(void **)(context + 0x30) = NNSi_FndAllocFromDefaultHeap(0x20);
    *(void **)(context + 0x34) = NNSi_FndAllocFromDefaultHeap(0x20);
    MIi_CpuCopy16(param + 0x1a0, *(void **)(context + 0x30), 0x20);
    MIi_CpuCopy16(param + 0x1c0, *(void **)(context + 0x34), 0x20);
    return (u32)UpdateBlinkPanel;
}
