#include "nitro/types.h"

extern u32 g_panelState_0206f9a0;
extern void func_ov027_020b7dfc(u32 panel);
extern void func_ov027_020b9a60(u32 panel);
extern void func_ov027_020b8c58(u32 panel);
extern void ZeroHalfThenFree_0202cd78(void *block);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_02051dfc(s32 mode);

void ShutdownPanelObjects_0206cea0(void)
{
    func_ov027_020b7dfc(g_panelState_0206f9a0);
    func_ov027_020b7dfc(g_panelState_0206f9a0 + 0x4c);
    func_ov027_020b9a60(g_panelState_0206f9a0 + 0xc990);
    func_ov027_020b8c58(g_panelState_0206f9a0 + 0x98);
    func_ov027_020b8c58(g_panelState_0206f9a0 + 0x6514);
    ZeroHalfThenFree_0202cd78(*(void **)(g_panelState_0206f9a0 + 0xcab4));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(g_panelState_0206f9a0 + 0xcab8));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(g_panelState_0206f9a0 + 0xcabc));
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)g_panelState_0206f9a0);
    func_02051dfc(9);
    func_02051dfc(10);
}
