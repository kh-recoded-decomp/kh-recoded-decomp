#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownOv082Screen(void);
extern void InitOv082EntryList(void);
extern void UpdateOv082EntryList(void);

void *data_ov082_020bf6a0[16] = {
    (void *)InitOv082EntryList,
    (void *)ShutdownOv082Screen,
    (void *)UpdateOv082EntryList,
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
