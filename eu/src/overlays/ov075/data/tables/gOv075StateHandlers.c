#include "nitro/types.h"

extern void OpenDefaultRectDialog(void);
extern void OpenPreviewDialog(void);
extern void UpdateSlotCursor(void);
extern void UpdateFlagToggleGrid(void);
extern void UpdateVolumeSlider(void);

void (*const gOv075StateHandlers[5])(void) = {
    OpenDefaultRectDialog,
    OpenPreviewDialog,
    UpdateSlotCursor,
    UpdateFlagToggleGrid,
    UpdateVolumeSlider,
};
