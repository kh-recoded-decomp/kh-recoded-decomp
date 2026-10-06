#include "nitro/types.h"

extern void func_ov001_0207a944(s32 panel);
extern void FreeBufferArray(s32 panel);
extern void func_ov001_0207ab68(s32 panel);
extern void NNSi_FndFreeFromDefaultHeap();
extern void SetDisplaySetting(u32 flag);

extern u32 data_ov001_020a04e8;

void func_ov001_0207ae58(void)
{
    s32 panel;

    panel = data_ov001_020a04e8;
    func_ov001_0207a944(data_ov001_020a04e8);
    FreeBufferArray(panel);
    func_ov001_0207ab68(panel);
    if (*(u32 *)(panel + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 4) = 0;
    }
    if (*(u32 *)(panel + 8) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 8) = 0;
    }
    if (*(u32 *)(panel + 0xc) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0xc) = 0;
    }
    if (*(u32 *)(panel + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0x10) = 0;
    }
    if (*(u32 *)(panel + 0x18) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0x18) = 0;
    }
    SetDisplaySetting(0);
    data_ov001_020a04e8 = 0;
}
