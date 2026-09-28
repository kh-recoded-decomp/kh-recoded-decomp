#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x12f];
    u16 unk_130;
    u8 pad_132[2];
    u8 unk_134;
    u8 unk_135;
} OverlaySelectionRecord;

extern u8 data_020608c8;

extern BOOL func_ov001_020645c8(u32 value);
extern void func_0204fbcc(u8 recordIndex, int kind);
extern void func_0204fda4(u8 recordIndex, int kind, int flags);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);

void SetupFlaggedSelectionRecords_0204f778(void)
{
    data_020608c8 = 1;
    if (func_ov001_020645c8(0x3609)) {
        func_0204fbcc(data_020608c8, 2);
        func_0204fda4(data_020608c8, 2, 0);
        data_020608c8++;
    }
    if (func_ov001_020645c8(0x360a)) {
        func_0204fbcc(data_020608c8, 1);
        func_0204fda4(data_020608c8, 1, 0);
        data_020608c8++;
    }
    if (data_020608c8 > 2) {
        GetOverlaySelectionRecord_0204f768(0)->unk_130 = 0xca;
        GetOverlaySelectionRecord_0204f768(0)->unk_134 = 0;
        GetOverlaySelectionRecord_0204f768(0)->unk_135 = 0;
    }
}
