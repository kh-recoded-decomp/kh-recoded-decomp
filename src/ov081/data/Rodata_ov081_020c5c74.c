#include "nitro/types.h"

extern void G2_GetBG0ScrPtr_02006de0(void);
extern void G2_GetBG1ScrPtr_02006e34(void);
extern void G2_GetBG2ScrPtr_02006e88(void);
extern void G2_GetBG3ScrPtr_02006f80(void);

void (*const data_ov081_020c5c74[4])(void) = {
    G2_GetBG0ScrPtr_02006de0,
    G2_GetBG1ScrPtr_02006e34,
    G2_GetBG2ScrPtr_02006e88,
    G2_GetBG3ScrPtr_02006f80,
};
