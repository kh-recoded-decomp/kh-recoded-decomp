#include "nitro/types.h"

typedef struct PaletteSource {
    u8 pad_00[0x14];
    u8 *data;
} PaletteSource;

typedef struct FieldManager {
    u8 pad_000[0x43c];
    u8 *altBuffer;
    u8 pad_440[8];
    u8 *mainBuffer;
    u8 pad_44c[0x1d0];
    PaletteSource *source;
} FieldManager;

typedef struct FieldManagerHandle {
    BOOL ready;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

void UploadScreenSlotBlock_02071770(int screen, int slot)
{
    FieldManager *manager = data_ov001_020a04a4.manager;
    int offset;
    u8 *data;

    if (screen != 0) {
        return;
    }
    switch (slot) {
    case 0:
        offset = 0;
        break;
    case 1:
        offset = 0x540;
        break;
    case 2:
        offset = 0xa80;
        break;
    default:
        offset = 0;
        break;
    }
    data = manager->source->data;
    if (manager->mainBuffer != NULL) {
        func_01ff878c(data + offset, manager->mainBuffer + 0x40, 0x540);
    } else if (manager->altBuffer != NULL) {
        func_01ff878c(data + offset, manager->altBuffer + 0x40, 0x540);
    } else {
        GFXi_EnqueueCommand_02014090((void *)7, 0x40, (int)(data + offset), 0x540);
    }
}
