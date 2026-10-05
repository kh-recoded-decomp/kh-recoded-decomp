#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CaptureRootHeap_020b9f54(void);
extern void ClearOverlayLoadQueues_020ba074(void);
extern void _fp_init_020b9f6c(void);
extern void func_ov027_020ba040(void);

void *data_ov027_020ba394[11] = {
    (void *)0x000E0012,
    (void *)func_ov027_020ba040,
    (void *)ClearOverlayLoadQueues_020ba074,
    (void *)0x00000018,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

void *data_ov027_020ba380[5] = {
    (void *)0x000E0011,
    (void *)CaptureRootHeap_020b9f54,
    (void *)_fp_init_020b9f6c,
    (void *)0x00000008,
    NULL,
};
