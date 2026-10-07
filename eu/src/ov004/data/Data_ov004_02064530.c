#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitScrollTextWork(void);
extern void ReleaseScrollTextWork(void);

void *data_ov004_02064530[5] = {
    (void *)0x00110008,
    (void *)InitScrollTextWork,
    (void *)ReleaseScrollTextWork,
    (void *)0x00030354,
    NULL,
};
