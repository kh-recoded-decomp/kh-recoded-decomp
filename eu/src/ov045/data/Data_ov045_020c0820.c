#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownScene(void);
extern void InitBattleGaugeContext(void);

void *data_ov045_020c0820[5] = {
    (void *)0x000E0017,
    (void *)InitBattleGaugeContext,
    (void *)ShutdownScene,
    (void *)0x00001A4C,
    NULL,
};
