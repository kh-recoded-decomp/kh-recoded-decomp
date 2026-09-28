#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x13b];
    u8 unk_13C[8];
} OverlaySelectionRecord;

extern void func_020506dc(int reload, int discardCached);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void func_02050ea4(void *list);
extern void func_02050a44(void);

void func_0204fba0(void)
{
    func_020506dc(0, 0);
    func_02050ea4(GetOverlaySelectionRecord_0204f768(0)->unk_13C);
    func_02050a44();
}
