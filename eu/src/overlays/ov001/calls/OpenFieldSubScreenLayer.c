#include "nitro/types.h"

typedef struct LayerSpec {
    u16 kind;
    u16 flags;
    int argument;
    int reserved[2];
} LayerSpec;

typedef struct FieldManager {
    u8 pad_000[0x42c];
    void *subLayer;
    u8 pad_430[0x50];
    u32 flags;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern const u8 data_ov045_020c0820[];
extern char OVERLAY_45_ID[];
extern void func_02029f8c(int processor, int overlayId);
extern void *func_0202a45c(const void *descriptor, LayerSpec *spec);

void OpenFieldSubScreenLayer(int argument)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    LayerSpec spec;

    func_02029f8c(0, (int)OVERLAY_45_ID);
    spec.kind = 3;
    spec.flags = 0;
    spec.argument = argument;
    if (manager->subLayer == NULL) {
        manager->flags &= ~1;
        manager->flags |= 0x40;
        manager->subLayer = func_0202a45c(data_ov045_020c0820, &spec);
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
    }
}
