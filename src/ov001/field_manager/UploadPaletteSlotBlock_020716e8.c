#include "nitro/types.h"

typedef struct PaletteSource {
    u8 pad_00[0xc];
    u8 *data;
} PaletteSource;

typedef struct PaletteSet {
    u8 colors[0x60];
} PaletteSet;

typedef struct FieldManager {
    u8 pad_000[0x444];
    u8 *altPalette;
    u8 pad_448[0x14];
    u8 *mainPalette;
    u8 pad_460[0x1c0];
    PaletteSource *source;
    PaletteSet sets[1];
} FieldManager;

typedef struct FieldManagerHandle {
    BOOL ready;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

void UploadPaletteSlotBlock_020716e8(int slot, int variant)
{
    FieldManager *manager = data_ov001_020a04a4.manager;
    int offset;
    u8 *src;

    switch (variant) {
    case 0:
        offset = 0;
        break;
    case 1:
        offset = 0x20;
        break;
    case 2:
        offset = 0x40;
        break;
    default:
        offset = 0;
        break;
    }
    if (slot == 0) {
        src = manager->source->data + offset;
    } else {
        src = manager->sets[slot - 1].colors + offset;
    }
    if (manager->mainPalette != NULL) {
        func_01ff878c(src, manager->mainPalette + 0x40 + slot * 0x20, 0x20);
    } else if (manager->altPalette != NULL) {
        func_01ff878c(src, manager->altPalette + 0x40 + slot * 0x20, 0x20);
    } else {
        GFXi_EnqueueCommand_02014090((void *)0xf, slot * 0x20 + 0x40, (int)src, 0x20);
    }
}
