#include "nitro/types.h"

extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void ClearBuffer2048_02078f00(void *dst);

void ClearSubBg2Screen_02078f34(void) {
    ClearBuffer2048_02078f00(G2S_GetBG2ScrPtr_02006f0c());
    *(volatile u16 *)0x0400100c &= 0x43;
}
