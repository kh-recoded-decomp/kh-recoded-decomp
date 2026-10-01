#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 savedY;
    u16 savedX;
} PlacementInfo;

typedef struct {
    u8 pad_00[0x1d4];
    PlacementInfo *placement;
} FieldEntry;

typedef struct {
    u8 pad_00[0x2a];
    u16 savedY;
    u16 savedX;
} ScreenState;

typedef struct {
    u8 pad_00[0x148];
    void *resourceA;
    void *resourceB;
} OverlayWork;

extern OverlayWork *data_ov040_020be260;
extern ScreenState *data_ov035_020bc4e0;
extern FieldEntry *GetBoundedEntryField_0206db5c(int index);
extern int func_ov035_020bafb4(void);
extern void func_ov001_02087214(void);
extern void func_ov019_020a3640(void);
extern void PXI_Init_0202a638(void *resource);
extern void func_ov001_020633d4(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void PopVramState_020365f0(void);

void ShutdownScreenWork_020bd990(void) {
    OverlayWork *work = data_ov040_020be260;
    data_ov035_020bc4e0->savedX = GetBoundedEntryField_0206db5c(0)->placement->savedX;
    data_ov035_020bc4e0->savedY = GetBoundedEntryField_0206db5c(0)->placement->savedY;
    if (func_ov035_020bafb4() >= 0) {
        func_ov035_020bafb4();
        func_ov001_02087214();
        func_ov019_020a3640();
    }
    PXI_Init_0202a638(work->resourceA);
    PXI_Init_0202a638(work->resourceB);
    func_ov001_020633d4();
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov040_020be260);
    data_ov040_020be260 = NULL;
    PopVramState_020365f0();
}
