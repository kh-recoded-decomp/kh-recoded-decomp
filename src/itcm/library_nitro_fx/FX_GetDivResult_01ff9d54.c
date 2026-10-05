#include "nitro/types.h"

int FX_GetDivResult_01ff9d54(void) {
    while (*(volatile u16 *)0x04000280 & 0x8000) {
    }
    return (int)((*(u64 *)0x040002a0 + 0x80000) >> 20);
}
