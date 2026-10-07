#include "nitro/types.h"

extern void G2_GetBG0ScrPtr(void);
extern void G2_GetBG1ScrPtr(void);
extern void G2_GetBG2ScrPtr(void);
extern void G2_GetBG3ScrPtr(void);

void *const data_ov081_020c5c94[4] = {
    (void *)G2_GetBG0ScrPtr,
    (void *)G2_GetBG1ScrPtr,
    (void *)G2_GetBG2ScrPtr,
    (void *)G2_GetBG3ScrPtr,
};
