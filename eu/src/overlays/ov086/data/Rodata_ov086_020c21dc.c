#include "nitro/types.h"

extern void ClearPanelElement(void);
extern void DrawPanelElement(void);

void *const gRecordPanelCallbacks[5] = {
    (void *)0x00000008,
    NULL,
    (void *)0x00000007,
    (void *)DrawPanelElement,
    (void *)ClearPanelElement,
};
