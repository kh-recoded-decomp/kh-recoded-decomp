#include "nitro/types.h"

extern void RunResetCallbackAndIdle_02004cf0(void);

void MIi_CheckAnotherAutoDMA_02005304(int dmaNo, u32 timing)
{
    int i;

    for (i = 0; i < 3; i++) {
        u32 cnt;

        if (i == dmaNo) {
            continue;
        }

        cnt = *(vu32 *)(0x040000b8 + i * 12);

        if ((cnt & 0x80000000) == 0) {
            continue;
        }

        cnt &= 0x38000000;

        if (cnt == timing) {
            continue;
        }
        if (cnt == 0x08000000 && timing == 0x10000000) {
            continue;
        }
        if (cnt == 0x10000000 && timing == 0x08000000) {
            continue;
        }
        if (cnt == 0x18000000 || cnt == 0x20000000 || cnt == 0x28000000 ||
            cnt == 0x30000000 || cnt == 0x38000000 || cnt == 0x08000000 ||
            cnt == 0x10000000) {
            RunResetCallbackAndIdle_02004cf0();
        }
    }
}
