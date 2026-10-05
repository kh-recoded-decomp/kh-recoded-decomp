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

extern OverlayWork *data_ov040_020be280;
extern ScreenState *data_ov035_020bc4e0;
extern FieldEntry *GetBoundedEntryField(int index);
extern int func_ov035_020bafd4(void);
extern void func_ov001_0208723c(void);
extern void ReleaseOwnedEntryGroup(void);
extern void PXI_Init_0202a64c(void *resource);
extern void FlushPendingFieldUpdate(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void PopVramState(void);

void ShutdownScreenWork(void) {
    OverlayWork *work = data_ov040_020be280;
    data_ov035_020bc4e0->savedX = GetBoundedEntryField(0)->placement->savedX;
    data_ov035_020bc4e0->savedY = GetBoundedEntryField(0)->placement->savedY;
    if (func_ov035_020bafd4() >= 0) {
        func_ov035_020bafd4();
        func_ov001_0208723c();
        ReleaseOwnedEntryGroup();
    }
    PXI_Init_0202a64c(work->resourceA);
    PXI_Init_0202a64c(work->resourceB);
    FlushPendingFieldUpdate();
    NNSi_FndFreeFromDefaultHeap(data_ov040_020be280);
    data_ov040_020be280 = NULL;
    PopVramState();
}
