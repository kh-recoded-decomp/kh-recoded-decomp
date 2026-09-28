#include "nitro/types.h"

extern int func_ov002_02066c78(int a, int b, int c, int d);
extern unsigned int func_0202a9d0(unsigned int range);
extern int g_context_0207e960;

void UpdatePlayerCounter_0206f5d8(void)
{
    int index;
    int counter;
    int cap;

    counter = func_ov002_02066c78(4, 0, 0, 0) + 1;
    cap = func_0202a9d0(200);
    if (counter > cap) {
        func_ov002_02066c78(0x80000005, 1, 0, 0);
        counter = 0;
    }
    index = *(int *)(g_context_0207e960 + 0xec);
    if (*(u8 *)(index * 0x70 + g_context_0207e960 + 0xcfbc) != 0 && func_0202a9d0(100) == 0x32) {
        counter = 0;
        func_ov002_02066c78(0x80000005, 1, 0, 0);
    }
    func_ov002_02066c78(0x80000004, counter, 0, 0);
}
