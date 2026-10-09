#include "nitro/types.h"

#pragma explicit_zero_data on

extern void func_ov075_020c49ec(void);
extern void UpdateMatrixMenuView(void);
extern void ShutdownMatrixMenu(void);
extern void func_ov075_020caf58(void);
extern void func_ov075_020cb198(void);
extern void func_ov075_020cb430(void);
extern void func_ov075_020cb678(void);
extern void ToggleMatrixOverview(void);
extern void HandleMatrixBackButton(void);
extern void TryOpenMatrixMenuThree(void);
extern void TryOpenMatrixMenuTwo(void);
extern void ToggleMatrixMapView(void);

void *gMatrixMenuHandlers[17] = {
    (void *)func_ov075_020c49ec,
    (void *)ShutdownMatrixMenu,
    (void *)UpdateMatrixMenuView,
    NULL,
    (void *)0x000178A8,
    (void *)func_ov075_020caf58,
    (void *)func_ov075_020cb198,
    (void *)func_ov075_020cb430,
    (void *)func_ov075_020cb678,
    (void *)ToggleMatrixOverview,
    (void *)HandleMatrixBackButton,
    NULL,
    NULL,
    (void *)TryOpenMatrixMenuThree,
    (void *)TryOpenMatrixMenuTwo,
    (void *)ToggleMatrixMapView,
    (void *)HandleMatrixBackButton,
};
