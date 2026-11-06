#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitProfilePanel(void);
extern void ShutdownPanelScene(void);

void *gProfilePanelTaskClass[5] = {
    (void *)0x00110008,
    (void *)InitProfilePanel,
    (void *)ShutdownPanelScene,
    (void *)0x00000130,
    NULL,
};
