#include "nitro/types.h"

extern void MI_StopDma_02005274(void);
extern void MIi_CardDmaCopy32_020056d4(void);

void (*const data_02052964[2])(void) = {
    MIi_CardDmaCopy32_020056d4,
    MI_StopDma_02005274,
};
