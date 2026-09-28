#include "nitro/types.h"

extern void func_ov001_0207a944(s32 panel);
extern void func_ov001_0207aadc(s32 panel);
extern void func_ov001_0207ab68(s32 panel);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern void func_02029f28(u32 flag);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207ae58(void)
{
    s32 panel;

    panel = g_activePanel_020a04c8;
    func_ov001_0207a944(g_activePanel_020a04c8);
    func_ov001_0207aadc(panel);
    func_ov001_0207ab68(panel);
    if (*(u32 *)(panel + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4();
        *(u32 *)(panel + 4) = 0;
    }
    if (*(u32 *)(panel + 8) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4();
        *(u32 *)(panel + 8) = 0;
    }
    if (*(u32 *)(panel + 0xc) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4();
        *(u32 *)(panel + 0xc) = 0;
    }
    if (*(u32 *)(panel + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4();
        *(u32 *)(panel + 0x10) = 0;
    }
    if (*(u32 *)(panel + 0x18) != 0) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4();
        *(u32 *)(panel + 0x18) = 0;
    }
    func_02029f28(0);
    g_activePanel_020a04c8 = 0;
}
