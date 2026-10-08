#include "nitro/types.h"

typedef struct {
    u8 icons[0x168];
    s32 bonusCount;
    s32 unlockBit;
} EntryInfo;

#ifndef OV101_COUNTS_OFFSET
#define OV101_COUNTS_OFFSET 0xCF00
#endif

typedef struct {
    u8 pad_0000[OV101_COUNTS_OFFSET];
    s32 counts[40];
} Ov101State;

extern const EntryInfo data_ov101_020c139c[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void ClearGlobalPackedBit_02027334(int bitIndex);
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);
extern void func_ov101_020c07d4(int setIndex, int bitIndex);

static inline void UpdateEntryUnlock(int index, int unlockBit)
{
    if (IsGlobalPackedBitSet_02027304(unlockBit)) {
        func_ov101_020c07d4(0, index);
        SetGlobalPackedBit_02027320(index + 0x11c2);
    }
    if (IsStateFlagSet_020c07a8(0, index) && !IsGlobalPackedBitSet_02027304(index + 0x1272) && IsGlobalPackedBitSet_02027304(index + 0x11c2)) {
        func_ov101_020c07d4(1, index);
    }
}

void RefreshEntryUnlocks_020c07f4(Ov101State *state)
{
    const EntryInfo *info;
    int unlockBit;
    int i;

    for (i = 0; i < 40; i++) {
        info = &data_ov101_020c139c[i];
        state->counts[i] = 0;
        if (i == 0x24) {
            UpdateEntryUnlock(i, info->unlockBit);
            state->counts[i] += info->bonusCount;
        } else {
            unlockBit = info->unlockBit;
            switch (i) {
            case 0:
                if (IsGlobalPackedBitSet_02027304(0xa0f)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11ee)) {
                        SetGlobalPackedBit_02027320(0x11ee);
                        ClearGlobalPackedBit_02027334(0x11c2);
                        ClearGlobalPackedBit_02027334(0x1272);
                    }
                    state->counts[i] += 1;
                }
                if (IsGlobalPackedBitSet_02027304(0xa11)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11ef)) {
                        SetGlobalPackedBit_02027320(0x11ef);
                        ClearGlobalPackedBit_02027334(0x11c2);
                        ClearGlobalPackedBit_02027334(0x1272);
                    }
                    state->counts[i] += 2;
                }
                break;
            case 1:
                if (IsGlobalPackedBitSet_02027304(0xa10)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11f0)) {
                        SetGlobalPackedBit_02027320(0x11f0);
                        ClearGlobalPackedBit_02027334(0x11c3);
                        ClearGlobalPackedBit_02027334(0x1273);
                    }
                    state->counts[i] += 9;
                }
                break;
            case 2:
                if (IsGlobalPackedBitSet_02027304(0xa10)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11f1)) {
                        SetGlobalPackedBit_02027320(0x11f1);
                        ClearGlobalPackedBit_02027334(0x11c4);
                        ClearGlobalPackedBit_02027334(0x1274);
                    }
                    state->counts[i] += 7;
                }
                break;
            case 3:
                if (IsGlobalPackedBitSet_02027304(0xa11)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11f2)) {
                        SetGlobalPackedBit_02027320(0x11f2);
                        ClearGlobalPackedBit_02027334(0x11c5);
                        ClearGlobalPackedBit_02027334(0x1275);
                    }
                    state->counts[i] += 4;
                }
                break;
            case 4:
            case 5:
            case 6:
                break;
            case 7:
                if (IsGlobalPackedBitSet_02027304(0xa0d)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11ea)) {
                        SetGlobalPackedBit_02027320(0x11ea);
                        ClearGlobalPackedBit_02027334(0x11c9);
                        ClearGlobalPackedBit_02027334(0x1279);
                    }
                    state->counts[i] += 1;
                }
                if (IsGlobalPackedBitSet_02027304(0xa0f)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11eb)) {
                        SetGlobalPackedBit_02027320(0x11eb);
                        ClearGlobalPackedBit_02027334(0x11c9);
                        ClearGlobalPackedBit_02027334(0x1279);
                    }
                    state->counts[i] += 3;
                }
                if (IsGlobalPackedBitSet_02027304(0xa10)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11ec)) {
                        SetGlobalPackedBit_02027320(0x11ec);
                        ClearGlobalPackedBit_02027334(0x11c9);
                        ClearGlobalPackedBit_02027334(0x1279);
                    }
                    state->counts[i] += 5;
                }
                if (IsGlobalPackedBitSet_02027304(0xa11)) {
                    if (!IsGlobalPackedBitSet_02027304(0x11ed)) {
                        SetGlobalPackedBit_02027320(0x11ed);
                        ClearGlobalPackedBit_02027334(0x11c9);
                        ClearGlobalPackedBit_02027334(0x1279);
                    }
                    state->counts[i] += 7;
                }
                break;
            }
            UpdateEntryUnlock(i, unlockBit);
            state->counts[i] += info->bonusCount;
        }
    }
}
