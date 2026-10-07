#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandlePopupBackInput(void);
extern void InitEntryMenu(void);
extern void ShutdownOverlay089(void);
extern void UpdateEntryCarousel(void);

void *data_ov089_020c056c[17] = {
    (void *)InitEntryMenu,
    (void *)ShutdownOverlay089,
    (void *)UpdateEntryCarousel,
    (void *)0x00000003,
    (void *)0x0000090C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)HandlePopupBackInput,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u32 data_ov089_020c0560[3] = {
    0x00000007, 0x00000006, 0x00000000,
};
