#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xca04];
    int recordPercent;
} EntryScene;

extern const int data_ov091_020c2ca8[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void ClearGlobalPackedBit_02027334(int bitIndex);
extern void SetEntryFlag_020c1718(int flagSet, int entryIndex);

void SyncRecordFlags_020c1400(EntryScene *scene)
{
    int i;
    int bit;
    int count;

    if (!IsGlobalPackedBitSet_02027304(0x1e17)) {
        ClearGlobalPackedBit_02027334(0x11e5);
        ClearGlobalPackedBit_02027334(0x11e7);
    }
    for (i = 0; i < 40; i++) {
        if (i == 36) {
            if (IsGlobalPackedBitSet_02027304(data_ov091_020c2ca8[i])) {
                SetGlobalPackedBit_02027320(i + 0x11c2);
                if (!IsGlobalPackedBitSet_02027304(i + 0x1272) && IsGlobalPackedBitSet_02027304(i + 0x11c2)) {
                    SetEntryFlag_020c1718(2, 4);
                }
            }
            continue;
        }
        bit = data_ov091_020c2ca8[i];
        switch (i) {
        case 0:
            if (IsGlobalPackedBitSet_02027304(0xa0f) && !IsGlobalPackedBitSet_02027304(0x11eb)) {
                SetGlobalPackedBit_02027320(0x11eb);
                ClearGlobalPackedBit_02027334(0x11c2);
                ClearGlobalPackedBit_02027334(0x1272);
            }
            if (IsGlobalPackedBitSet_02027304(0xa11) && !IsGlobalPackedBitSet_02027304(0x11ec)) {
                SetGlobalPackedBit_02027320(0x11ec);
                ClearGlobalPackedBit_02027334(0x11c2);
                ClearGlobalPackedBit_02027334(0x1272);
            }
            break;
        case 1:
            if (IsGlobalPackedBitSet_02027304(0xa10) && !IsGlobalPackedBitSet_02027304(0x11ed)) {
                SetGlobalPackedBit_02027320(0x11ed);
                ClearGlobalPackedBit_02027334(0x11c3);
                ClearGlobalPackedBit_02027334(0x1273);
            }
            break;
        case 2:
            if (IsGlobalPackedBitSet_02027304(0xa10) && !IsGlobalPackedBitSet_02027304(0x11ee)) {
                SetGlobalPackedBit_02027320(0x11ee);
                ClearGlobalPackedBit_02027334(0x11c4);
                ClearGlobalPackedBit_02027334(0x1274);
            }
            break;
        case 3:
            if (IsGlobalPackedBitSet_02027304(0xa11) && !IsGlobalPackedBitSet_02027304(0x11ef)) {
                SetGlobalPackedBit_02027320(0x11ef);
                ClearGlobalPackedBit_02027334(0x11c5);
                ClearGlobalPackedBit_02027334(0x1275);
            }
            break;
        case 7:
            if (IsGlobalPackedBitSet_02027304(0xa10) && !IsGlobalPackedBitSet_02027304(0x11ea)) {
                SetGlobalPackedBit_02027320(0x11ea);
                ClearGlobalPackedBit_02027334(0x11c9);
                ClearGlobalPackedBit_02027334(0x1279);
            }
            break;
        }
        if (IsGlobalPackedBitSet_02027304(bit)) {
            SetGlobalPackedBit_02027320(i + 0x11c2);
            if (!IsGlobalPackedBitSet_02027304(i + 0x1272) && IsGlobalPackedBitSet_02027304(i + 0x11c2)) {
                SetEntryFlag_020c1718(2, 4);
            }
        }
    }
    count = 0;
    for (bit = 0x11c2; bit < 0x11c2 + 46; bit++) {
        if (IsGlobalPackedBitSet_02027304(bit)) {
            count++;
        }
    }
    scene->recordPercent = count * 100 / 46;
}
