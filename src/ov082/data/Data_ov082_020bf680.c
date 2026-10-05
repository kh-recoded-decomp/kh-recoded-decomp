#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv082EntryList_020beaa0(void);
extern void ShutdownOv082Screen_020bf300(void);
extern void UpdateOv082EntryList_020bf370(void);

void *data_ov082_020bf680[16] = {
    (void *)InitOv082EntryList_020beaa0,
    (void *)ShutdownOv082Screen_020bf300,
    (void *)UpdateOv082EntryList_020bf370,
    (void *)0x0000372C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
