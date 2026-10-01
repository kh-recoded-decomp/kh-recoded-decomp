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

extern FieldManagerHandle data_ov001_020a04a4;
extern const u8 data_020c0800[];
extern char OverlayId45_0000002d[];
extern void func_02029f78(int processor, int overlayId);
extern void *func_0202a448(const void *descriptor, LayerSpec *spec);

void OpenFieldSubScreenLayer_02071d6c(int argument)
{
    FieldManager *manager = data_ov001_020a04a4.manager;
    LayerSpec spec;

    func_02029f78(0, (int)OverlayId45_0000002d);
    spec.kind = 3;
    spec.flags = 0;
    spec.argument = argument;
    if (manager->subLayer == NULL) {
        manager->flags &= ~1;
        manager->flags |= 0x40;
        manager->subLayer = func_0202a448(data_020c0800, &spec);
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
    }
}
