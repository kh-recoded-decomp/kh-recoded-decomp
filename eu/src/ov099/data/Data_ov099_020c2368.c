#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandleListCursorUp(void);
extern void UpdateModelViewerScreen(void);
extern void func_ov099_020becb4(void);
extern void func_ov099_020bedd0(void);

void *data_ov099_020c2368[6] = {
    (void *)func_ov099_020becb4,
    (void *)func_ov099_020bedd0,
    (void *)UpdateModelViewerScreen,
    (void *)0x00000008,
    (void *)0x0000D6F8,
    (void *)HandleListCursorUp,
};
