#include "nitro/types.h"

typedef struct {
    int id;
    int type;
    int alwaysVisible;
    int revealBit;
} AchievementDef;

typedef struct {
    int index;
    AchievementDef *def;
    int progress;
} AchievementRow;

typedef struct {
    u8 pad_0000[0xcfec];
    AchievementRow rows[36];
    int rowCount;
    u8 pad_d1a0[0x40];
    int newUnlockCount;
} AchievementScene;

typedef struct {
    int offset;
    int width;
} PackedField;

typedef struct {
    int kind;
    int value;
} ProgressCheck;

typedef struct {
    u32 offset;
    u32 maxValue;
} FieldLimit;

extern AchievementDef *func_ov093_020c2c7c(int index);
extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22d4(int flagSet, int entryIndex);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern int ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern int func_020275e4(void);
extern u16 AddRecordItem_02029240(int index, const void *src);
extern int GetUnlockedSlotValue_02051270(u32 index);
extern const int data_ov093_020c4090[];

typedef struct {
    PackedField fields[6];
} TotalFieldTable;

typedef struct {
    int values[5];
} IntList5;

typedef struct {
    int values[8];
} IntList8;

typedef struct {
    u32 values[8];
} CountList8;

typedef struct {
    int values[36];
} IntList36;

extern const TotalFieldTable data_ov093_020c3d94;
extern const IntList8 data_ov093_020c3cf4;
extern const CountList8 data_ov093_020c3d14;
extern const IntList5 data_ov093_020c3c40;
extern const IntList5 data_ov093_020c3c68;
extern const IntList8 data_ov093_020c3d54;
extern const IntList8 data_ov093_020c3cb4;
extern const IntList8 data_ov093_020c3cd4;
extern const IntList8 data_ov093_020c3d34;
extern const IntList8 data_ov093_020c3d74;
extern const IntList36 data_ov093_020c3dc4;
extern const ProgressCheck data_ov093_020c45bc[];
extern const FieldLimit data_ov093_020c3fb4[];

static inline void UnlockAchievement(AchievementScene *scene, int id)
{
    if (!IsEntryFlagSet_020c22a4(0, id)) {
        SetEntryFlag_020c22d4(1, id);
        scene->newUnlockCount++;
        AddRecordItem_02029240(0xca, 0);
        SetGlobalPackedBit_02027320(0xca);
        SetGlobalPackedBit_02027320(id + 0x1152);
    }
    if (!IsGlobalPackedBitSet_02027304(id + 0x1202) && IsGlobalPackedBitSet_02027304(id + 0x1152)) {
        SetEntryFlag_020c22d4(4, id);
    }
}

void BuildAchievementList_020c0fb0(AchievementScene *scene)
{
    int i;
    AchievementRow *row;
    int group;
    int bit;
    u32 k;
    u32 total;
    for (i = 0; i < 36; i++) {
        AchievementDef *def = func_ov093_020c2c7c(i);
        int type = def->type;
        int id = def->id;
        row = &scene->rows[scene->rowCount];
        row->index = i;
        row->def = def;
        switch (type) {
        case 0:
            if (id == -1) {
                switch (i) {
                case 0: {
                    int offset;
                    int j;
                    row->progress = 0;
                    for (j = 0, offset = 0x680; j < 40; j++, offset += 0x11) {
                        row->progress += ReadGlobalPackedBits_02027348(offset, 0x11);
                    }
                    if (row->progress >= 99999) {
                        row->progress = 99999;
                    }
                    break;
                }
                case 1:
                case 2:
                case 3:
                case 4:
                case 5: {
                    TotalFieldTable table = data_ov093_020c3d94;
                    int limit = 99999;
                    if (i == 5) {
                        limit = 9999;
                    }
                    row->progress = ReadGlobalPackedBits_02027348(table.fields[i].offset, table.fields[i].width);
                    if (row->progress > limit) {
                        row->progress = limit;
                    }
                    break;
                }
                }
            }
            break;
        case 1: {
            int count = 0;
            switch (id) {
            case 0: {
                IntList8 bitStarts = data_ov093_020c3cf4;
                CountList8 bitCounts = data_ov093_020c3d14;
                for (group = 0; group < 8; group++) {
                    total = bitCounts.values[group];
                    bit = bitStarts.values[group];
                    for (k = 0; k < total; k++) {
                        if (IsGlobalPackedBitSet_02027304(bit)) {
                            count++;
                        }
                        bit++;
                    }
                }
                row->progress = count * 100 / 111;
                break;
            }
            case 1: {
                int bit;
                int k;
                for (k = 0, bit = 0x5c0; k < 192; k++, bit++) {
                    if (IsGlobalPackedBitSet_02027304(bit)) {
                        count++;
                    }
                }
                row->progress = count * 100 / 92;
                break;
            }
            case 2: {
                int bit;
                int k;
                for (k = 0, bit = 0x9b0; k < 25; k++, bit++) {
                    if (IsGlobalPackedBitSet_02027304(bit)) {
                        count++;
                    }
                }
                row->progress = count * 100 / 25;
                break;
            }
            case 3:
                row->progress = ReadGlobalPackedBits_02027348(0xbf0, 8) * 100 / 200;
                break;
            case 4: {
                IntList5 bits = data_ov093_020c3c40;
                int k;
                for (k = 0; k < 5; k++) {
                    if (IsGlobalPackedBitSet_02027304(bits.values[k])) {
                        count++;
                    }
                }
                row->progress = count * 100 / 5;
                break;
            }
            case 5: {
                int owned[32];
                int ownedCount = 0;
                int slot;
                int j;
                for (slot = 0; slot < 32; slot++) {
                    int value = GetUnlockedSlotValue_02051270(slot);
                    if (value != -1) {
                        owned[ownedCount] = value;
                        ownedCount++;
                    }
                }
                for (j = 0; j < 239; j++) {
                    const ProgressCheck *check = &data_ov093_020c45bc[j];
                    int bit;
                    switch (check->kind) {
                    case 0:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        bit = check->value;
                        break;
                    case 1: {
                        int k;
                        for (k = 0; k < ownedCount; k++) {
                            if (check->value == owned[k]) {
                                count++;
                                break;
                            }
                        }
                        continue;
                    }
                    case 2:
                        switch (check->value) {
                        case 6:
                            bit = 0xbeb;
                            break;
                        case 8:
                            bit = 0xbec;
                            break;
                        case 10:
                            bit = 0xbed;
                            break;
                        case 12:
                            bit = 0xbee;
                            break;
                        case 14:
                            bit = 0xbef;
                            break;
                        default:
                            continue;
                        }
                        break;
                    default:
                        continue;
                    }
                    if (IsGlobalPackedBitSet_02027304(bit)) {
                        count++;
                    }
                }
                row->progress = count * 100 / 239;
                break;
            }
            case 6:
                row->progress = func_020275e4() * 100 / 815;
                break;
            case 11: {
                int offset;
                int k;
                for (k = 0, offset = 0x680; k < 40; k++, offset += 0x11) {
                    if (ReadGlobalPackedBits_02027348(offset, 0x11) != 0) {
                        count++;
                    }
                }
                row->progress = count * 100 / 40;
                break;
            }
            case 12: {
                int bit;
                int k;
                for (k = 0, bit = 0xbd9; k < 11; k++, bit++) {
                    if (IsGlobalPackedBitSet_02027304(bit)) {
                        count++;
                    }
                }
                row->progress = count * 100 / 11;
                break;
            }
            case 15: {
                int bit;
                int k;
                for (k = 0, bit = 0xb59; k < 93; k++, bit++) {
                    if (IsGlobalPackedBitSet_02027304(bit)) {
                        count++;
                    }
                }
                row->progress = count * 100 / 93;
                break;
            }
            case 17: {
                IntList5 fields = data_ov093_020c3c68;
                int k;
                for (k = 0; k < 5; k++) {
                    count += ReadGlobalPackedBits_02027348(fields.values[k], 2);
                }
                row->progress = count * 100 / 15;
                break;
            }
            case 18: {
                IntList8 bits = data_ov093_020c3d54;
                int k;
                for (k = 0; k < 8; k++) {
                    if (IsGlobalPackedBitSet_02027304(bits.values[k])) {
                        count++;
                    }
                }
                row->progress = count * 100 / 8;
                break;
            }
            case 19: {
                IntList8 bits = data_ov093_020c3cb4;
                int k;
                for (k = 0; k < 8; k++) {
                    if (IsGlobalPackedBitSet_02027304(bits.values[k])) {
                        count++;
                    }
                }
                row->progress = count * 100 / 8;
                break;
            }
            case 20: {
                IntList8 bits = data_ov093_020c3cd4;
                int k;
                for (k = 0; k < 8; k++) {
                    if (IsGlobalPackedBitSet_02027304(bits.values[k])) {
                        count++;
                    }
                }
                row->progress = count * 100 / 8;
                break;
            }
            case 21: {
                IntList8 bits = data_ov093_020c3d34;
                IntList8 fields = data_ov093_020c3d74;
                int k;
                for (k = 0; k < 8; k++) {
                    if (IsGlobalPackedBitSet_02027304(bits.values[k])) {
                        int value = ReadGlobalPackedBits_02027348(fields.values[k], 7);
                        if (value >= 0 && value <= 14) {
                            count++;
                        }
                    }
                }
                row->progress = count * 100 / 8;
                break;
            }
            default:
                row->progress = 100;
                break;
            }
            if (row->progress >= data_ov093_020c4090[id]) {
                UnlockAchievement(scene, id);
                if (id == 19 && IsEntryFlagSet_020c22a4(1, 19) && !IsEntryFlagSet_020c22a4(0, 18) && !IsEntryFlagSet_020c22a4(1, 18)) {
                    UnlockAchievement(scene, 18);
                }
            }
            break;
        }
        case 2: {
            IntList36 unlockBits = data_ov093_020c3dc4;
            int bit = unlockBits.values[id];
            BOOL unlocked = FALSE;
            if (i == 13) {
                if (ReadGlobalPackedBits_02027348(0x9f0, 7) == 100) {
                    unlocked = TRUE;
                }
            } else {
                unlocked = IsGlobalPackedBitSet_02027304(bit);
            }
            if (unlocked) {
                int slot = i - 28;
                switch (slot) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                {
                    const FieldLimit *limit = &data_ov093_020c3fb4[slot];
                    if ((u32)ReadGlobalPackedBits_02027348(limit->offset, 0x11) > limit->maxValue) {
                        unlocked = FALSE;
                    }
                    break;
                }
                }
            }
            row->progress = unlocked;
            if (unlocked == data_ov093_020c4090[id]) {
                UnlockAchievement(scene, id);
            }
            break;
        }
        }
        if (def->alwaysVisible == 0 && def->id != -1) {
            if (def->revealBit != 0 && IsGlobalPackedBitSet_02027304(def->revealBit)) {
                scene->rowCount++;
                continue;
            }
            if (!IsEntryFlagSet_020c22a4(0, id) && !IsEntryFlagSet_020c22a4(1, id)) {
                continue;
            }
        }
        scene->rowCount++;
    }
}
