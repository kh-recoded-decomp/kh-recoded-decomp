#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0xf];
    u8 unk_010;
} OverlaySelectionRecord;

typedef struct SelectionState {
    u8 recordCount;
    u8 pad_01[3];
    int taggedCount;
    u32 savedByte;
} SelectionState;

typedef struct PackedValueBlock {
    u32 savedByte;
    u16 values[3];
} PackedValueBlock;

typedef struct BitOffsetTable {
    u32 offsets[3];
} BitOffsetTable;

extern const BitOffsetTable data_02055a2c;
extern SelectionState data_020608c8;
extern PackedValueBlock data_020608d0;
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);

void LoadSelectionPackedValues_0205053c(void)
{
    BitOffsetTable table = data_02055a2c;
    int i;

    i = 0;
    data_020608c8.savedByte = GetOverlaySelectionRecord_0204f768(0)->unk_010;
    do {
        data_020608d0.values[i] = ReadGlobalPackedBits_02027348(table.offsets[i], 0x10);
        i++;
    } while (i < 3);
}
