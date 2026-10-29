#include "nitro/types.h"
#include "src/overlays/ov074/RootMenu.h"

#pragma explicit_zero_data on

extern void HandleRootMenuCancel(void);
extern void ReleaseRootMenu(void);
extern void SelectNextRootMenuItem(void);
extern void SelectPreviousRootMenuItem(void);
extern void ToggleRootMenuOptionLeft(void);
extern void ToggleRootMenuOptionRight(void);
extern void InitRootMenu(void);
extern void UpdateRootMenuFrame(void);

void *gRootMenuDefinition[17] = {
    (void *)InitRootMenu,
    (void *)ReleaseRootMenu,
    (void *)UpdateRootMenuFrame,
    NULL,
    (void *)sizeof(RootMenu),
    (void *)SelectPreviousRootMenuItem,
    (void *)SelectNextRootMenuItem,
    (void *)ToggleRootMenuOptionLeft,
    (void *)ToggleRootMenuOptionRight,
    (void *)HandleRootMenuConfirm,
    (void *)HandleRootMenuCancel,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)HandleRootMenuCancel,
};
