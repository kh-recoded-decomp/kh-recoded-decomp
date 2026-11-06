#include "nitro/types.h"

extern void ClearWidgetOnScreenLayer(void);
extern void DrawWidgetOnScreenLayer(void);

const u32 gMenuImageFileTags[7] = {
    0x73006D63, 0x76730076, 0x00767300, 0x73007673,
    0x70730076, 0x00737700, 0x00007363,
};

void *const gMenuBackgroundContainerConfig[5] = {
    (void *)0x00000030,
    (void *)0x00000020,
    (void *)0x00000010,
    (void *)DrawWidgetOnScreenLayer,
    (void *)ClearWidgetOnScreenLayer,
};

const u32 gMenuSubBgLayerIds[4] = {
    0x00000018, 0x00000019, 0x0000001A, 0x0000001B,
};

const u32 gMenuMainBgLayerIds[3] = {
    0x00000009, 0x0000000A, 0x0000000B,
};

const u32 gMenuKeyRepeatConfig[1] = {
    0x0002000C,
};
