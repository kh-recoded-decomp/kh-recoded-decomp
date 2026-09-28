#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov001_0206c204(int base);
extern void func_ov001_0206bf34(int base);
extern void func_ov001_0206c720(u32 address);

extern u32 g_manager_020a0484;

void func_ov001_0206ae58(void)
{
    int heap;

    heap = (int)NNSi_FndGetCurrentRootHeap_0202a764();
    func_ov001_0206c204(heap + 0x50);
    func_ov001_0206bf34(heap + 0xcc);
    func_ov001_0206c720(0x206c46d);
    g_manager_020a0484 = 0;
}
