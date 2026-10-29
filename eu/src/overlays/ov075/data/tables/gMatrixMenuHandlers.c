#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMatrixMenu(void);
extern void UpdateMatrixMenuView(void);
extern void ShutdownMatrixMenu(void);
extern void MoveMatrixCursorUp_020caf38(void);
extern void MoveMatrixCursorDown_020cb178(void);
extern void MoveMatrixCursorLeft_020cb410(void);
extern void MoveMatrixCursorRight(void);
extern void ToggleMatrixOverview(void);
extern void HandleMatrixBackButton(void);
extern void TryOpenMatrixMenuThree(void);
extern void TryOpenMatrixMenuTwo(void);
extern void ToggleMatrixMapView(void);

void *gMatrixMenuHandlers[17] = {
    (void *)InitMatrixMenu,
    (void *)ShutdownMatrixMenu,
    (void *)UpdateMatrixMenuView,
    NULL,
    (void *)0x000178A8,
    (void *)MoveMatrixCursorUp_020caf38,
    (void *)MoveMatrixCursorDown_020cb178,
    (void *)MoveMatrixCursorLeft_020cb410,
    (void *)MoveMatrixCursorRight,
    (void *)ToggleMatrixOverview,
    (void *)HandleMatrixBackButton,
    NULL,
    NULL,
    (void *)TryOpenMatrixMenuThree,
    (void *)TryOpenMatrixMenuTwo,
    (void *)ToggleMatrixMapView,
    (void *)HandleMatrixBackButton,
};
