#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandlePopupBackInput_020c0068(void);
extern void InitEntryMenu_020c00e4(void);
extern void ShutdownOverlay089_020c01b4(void);
extern void UpdateEntryCarousel_020c01f4(void);

void *data_ov089_020c054c[17] = {
    (void *)InitEntryMenu_020c00e4,
    (void *)ShutdownOverlay089_020c01b4,
    (void *)UpdateEntryCarousel_020c01f4,
    (void *)0x00000003,
    (void *)0x0000090C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)HandlePopupBackInput_020c0068,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u32 data_ov089_020c0540[3] = {
    0x00000007, 0x00000006, 0x00000000,
};
