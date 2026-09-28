#include "nitro/types.h"

extern short *func_02025d08(int scriptCtx, unsigned short *operand);
extern int func_0202b788(void);

int func_02025dac(int scriptCtx, unsigned short *operand)
{
    int base = scriptCtx + 4 + *(int *)(scriptCtx + 0x1c4) * 0x70;
    short *resolved = func_02025d08(scriptCtx, operand);

    if (*resolved == 0x40) {
        int indexBase = *(int *)(base + 0x14) + *(volatile int *)(resolved + 2);
        int selector = func_0202b788();
        return *(int *)(base + 0x14) + *(int *)(indexBase + selector * 4);
    }
    return *(int *)(base + 0x14) + *(volatile int *)(resolved + 2);
}

