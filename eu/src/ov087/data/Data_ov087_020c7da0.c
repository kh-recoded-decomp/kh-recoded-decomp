#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyPanelScene(void);
extern void SwitchToSecondaryIfEntryRejected(void);
extern void PanelScene_HandleCancel(void);
extern void InitPanelScene_020c713c(void);
extern void UpdateEntryScroll(void);

void *data_ov087_020c7da0[17] = {
    (void *)InitPanelScene_020c713c,
    (void *)DestroyPanelScene,
    (void *)UpdateEntryScroll,
    (void *)0x00000002,
    (void *)0x00000BE0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)PanelScene_HandleCancel,
    (void *)SwitchToSecondaryIfEntryRejected,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
