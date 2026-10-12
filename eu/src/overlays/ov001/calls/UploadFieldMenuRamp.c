#include "src/overlays/ov001/FieldMenuPalettes.h"

typedef struct FieldMenuPaletteState {
    u8 reserved000[0x104];
    s32 mode;
} FieldMenuPaletteState;

extern BOOL NNS_GfdRegisterNewVramTransferTask(u32 type, u32 destination, const void *source, u32 size);

void UploadFieldMenuRamp(FieldMenuPaletteState *menu, BOOL alternate)
{
    if (alternate) {
        NNS_GfdRegisterNewVramTransferTask(15, 0x30, gFieldMenuAlternateRamps[menu->mode], 6);
        return;
    }
    NNS_GfdRegisterNewVramTransferTask(15, 0x30, gFieldMenuNormalRamps[menu->mode], 6);
}
