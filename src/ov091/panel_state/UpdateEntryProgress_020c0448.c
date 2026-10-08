#include "nitro/types.h"

typedef struct {
    int id;
    int type;
    int hidden;
} FlagRecord;

typedef struct {
    int index;
    FlagRecord *record;
    int progress;
} ProgressEntry;

typedef struct {
    u8 pad_00[0xc9f4];
    int unlockedTotal;
    u8 pad_c9f8[0x14];
    ProgressEntry entries[36];
    int entryCount;
} EntryScene;

typedef struct {
    int offset;
    int width;
} BitField;

typedef struct {
    int offset;
    u32 max;
} FieldLimit;

typedef struct {
    int kind;
    int value;
} Requirement;

typedef struct {
    BitField fields[6];
} CounterFields;

typedef struct {
    int bits[8];
} BitList8;

typedef struct {
    u32 counts[8];
} CountList8;

typedef struct {
    int bits[5];
} BitList5;

typedef struct {
    int bits[36];
} BitList36;

extern const CounterFields data_ov091_020c2930;
extern const BitList8 data_ov091_020c28b0;
extern const CountList8 data_ov091_020c28d0;
extern const BitList5 data_ov091_020c283c;
extern const BitList5 data_ov091_020c2828;
extern const BitList8 data_ov091_020c2910;
extern const BitList8 data_ov091_020c2850;
extern const BitList36 data_ov091_020c2960;
extern const BitList8 data_ov091_020c2890;
extern const BitList8 data_ov091_020c28f0;
extern const BitList8 data_ov091_020c2870;
extern const FieldLimit data_ov091_020c2ab8[];
extern const int data_ov091_020c2b3c[];
extern const Requirement data_ov091_020c2de8[];

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern int ReadGlobalPackedBits_02027348(int bitOffset, int bitCount);
extern int func_020275e4(void);
extern int func_02051270(int slot);
extern BOOL IsEntryFlagSet_020c16e8(int flagSet, int entryIndex);
extern void SetEntryFlag_020c1718(int flagSet, int entryIndex);
extern FlagRecord *GetPlayerFlagRecord_020c2800(int index);

void UpdateEntryProgress_020c0448(EntryScene *scene)
{
    int i;
    int bit;
    FlagRecord *record;
    int index;
    int countA;
    int countB;

    bit = 0xf1a;
    for (i = 0; i < 30; i++) {
        if (IsGlobalPackedBitSet_02027304(bit)) {
            SetEntryFlag_020c1718(0, i);
        }
        bit++;
    }
    for (index = 0; index < 36; index++) {
        ProgressEntry *entry;
        int type;
        int id;

        record = GetPlayerFlagRecord_020c2800(index);
        type = record->type;
        id = record->id;
        entry = &scene->entries[scene->entryCount];

        entry->index = index;
        entry->record = record;
        switch (type) {
        case 0:
            if (id != -1) {
                break;
            }
            switch (index) {
            case 0: {
                int fieldBit;
                int j;
                entry->progress = 0;
                fieldBit = 0x680;
                for (j = 0; j < 40; j++) {
                    entry->progress += ReadGlobalPackedBits_02027348(fieldBit, 17);
                    fieldBit += 17;
                }
                if (entry->progress >= 99999) {
                    entry->progress = 99999;
                }
                break;
            }
            case 1:
            case 2:
            case 3:
            case 4:
            case 5: {
                CounterFields counters = data_ov091_020c2930;
                int limit = 99999;
                if (index == 5) {
                    limit = 9999;
                }
                entry->progress = ReadGlobalPackedBits_02027348(counters.fields[index].offset, counters.fields[index].width);
                if (entry->progress > limit) {
                    entry->progress = limit;
                }
                break;
            }
            }
            break;
        case 1: {
            int k;
            int scanBit;
            int j;
            u32 length;
            int count;

            count = 0;
            switch (id) {
            case 0: {
                BitList8 starts = data_ov091_020c28b0;
                CountList8 lengths = data_ov091_020c28d0;
                for (k = 0; k < 8; k++) {
                    length = lengths.counts[k];
                    scanBit = starts.bits[k];
                    for (j = 0; j < length; j++) {
                        if (IsGlobalPackedBitSet_02027304(scanBit)) {
                            count++;
                        }
                        scanBit++;
                    }
                }
                entry->progress = count * 100 / 111;
                break;
            }
            case 1: {
                scanBit = 0x5c0;
                for (j = 0; j < 192; j++) {
                    if (IsGlobalPackedBitSet_02027304(scanBit)) {
                        count++;
                    }
                    scanBit++;
                }
                entry->progress = count * 100 / 92;
                break;
            }
            case 2: {
                scanBit = 0x9b0;
                for (j = 0; j < 25; j++) {
                    if (IsGlobalPackedBitSet_02027304(scanBit)) {
                        count++;
                    }
                    scanBit++;
                }
                entry->progress = count * 100 / 25;
                break;
            }
            case 3:
                entry->progress = ReadGlobalPackedBits_02027348(0xbf0, 8) * 100 / 200;
                break;
            case 4: {
                BitList5 bits = data_ov091_020c283c;
                for (j = 0; j < 5; j++) {
                    if (IsGlobalPackedBitSet_02027304(bits.bits[j])) {
                        count++;
                    }
                }
                entry->progress = count * 100 / 5;
                break;
            }
            case 5: {
                int owned[32];
                int ownedCount = 0;
                int n;
                for (n = 0; n < 32; n++) {
                    int item = func_02051270(n);
                    if (item != -1) {
                        owned[ownedCount] = item;
                        ownedCount++;
                    }
                }
                for (n = 0; n < 239; n++) {
                    const Requirement *req = &data_ov091_020c2de8[n];
                    int reqBit;
                    switch (req->kind) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                        reqBit = req->value;
                        break;
                    case 5: {
                                for (k = 0; k < ownedCount; k++) {
                            if (req->value == owned[k]) {
                                count++;
                                break;
                            }
                        }
                        continue;
                    }
                    case 6:
                        switch (req->value) {
                        case 6:
                            reqBit = 0xbeb;
                            break;
                        case 8:
                            reqBit = 0xbec;
                            break;
                        case 10:
                            reqBit = 0xbed;
                            break;
                        case 12:
                            reqBit = 0xbee;
                            break;
                        case 14:
                            reqBit = 0xbef;
                            break;
                        default:
                            continue;
                        }
                        break;
                    default:
                        continue;
                    }
                    if (IsGlobalPackedBitSet_02027304(reqBit)) {
                        count++;
                    }
                }
                entry->progress = count * 100 / 239;
                break;
            }
            case 6:
                entry->progress = func_020275e4() * 100 / 815;
                break;
            case 11: {
                scanBit = 0x680;
                for (j = 0; j < 40; j++) {
                    if (ReadGlobalPackedBits_02027348(scanBit, 17) >= 1) {
                        count++;
                    }
                    scanBit += 17;
                }
                entry->progress = count * 100 / 40;
                break;
            }
            case 12: {
                scanBit = 0xbd9;
                for (j = 0; j < 11; j++) {
                    if (IsGlobalPackedBitSet_02027304(scanBit)) {
                        count++;
                    }
                    scanBit++;
                }
                entry->progress = count * 100 / 11;
                break;
            }
            case 15: {
                scanBit = 0xb59;
                for (j = 0; j < 93; j++) {
                    if (IsGlobalPackedBitSet_02027304(scanBit)) {
                        count++;
                    }
                    scanBit++;
                }
                entry->progress = count * 100 / 93;
                break;
            }
            case 17: {
                BitList5 fields = data_ov091_020c2828;
                for (j = 0; j < 5; j++) {
                    count += ReadGlobalPackedBits_02027348(fields.bits[j], 2);
                }
                entry->progress = count * 100 / 15;
                break;
            }
            case 18: {
                BitList8 bits = data_ov091_020c2850;
                for (j = 0; j < 8; j++) {
                    if (IsGlobalPackedBitSet_02027304(bits.bits[j])) {
                        count++;
                    }
                }
                entry->progress = count * 100 / 8;
                break;
            }
            case 19: {
                BitList8 bits = data_ov091_020c2890;
                for (j = 0; j < 8; j++) {
                    if (IsGlobalPackedBitSet_02027304(bits.bits[j])) {
                        count++;
                    }
                }
                entry->progress = count * 100 / 8;
                break;
            }
            case 20: {
                BitList8 bits = data_ov091_020c28f0;
                for (j = 0; j < 8; j++) {
                    if (IsGlobalPackedBitSet_02027304(bits.bits[j])) {
                        count++;
                    }
                }
                entry->progress = count * 100 / 8;
                break;
            }
            case 21: {
                BitList8 flags = data_ov091_020c2870;
                BitList8 levels = data_ov091_020c2910;
                for (j = 0; j < 8; j++) {
                    if (IsGlobalPackedBitSet_02027304(flags.bits[j])) {
                        int level = ReadGlobalPackedBits_02027348(levels.bits[j], 7);
                        if (level >= 0 && level <= 14) {
                            count++;
                        }
                    }
                }
                entry->progress = count * 100 / 8;
                break;
            }
            default:
                entry->progress = 100;
                break;
            }
            if (entry->progress >= data_ov091_020c2b3c[id]) {
                if (!IsEntryFlagSet_020c16e8(0, id)) {
                    SetEntryFlag_020c1718(1, id);
                    SetGlobalPackedBit_02027320(id + 0x1152);
                }
                if (!IsGlobalPackedBitSet_02027304(id + 0x1202) && IsGlobalPackedBitSet_02027304(id + 0x1152)) {
                    SetEntryFlag_020c1718(2, 0);
                }
                if (id == 19 && IsEntryFlagSet_020c16e8(1, 19) && !IsEntryFlagSet_020c16e8(0, 18) && !IsEntryFlagSet_020c16e8(1, 18)) {
                    if (!IsEntryFlagSet_020c16e8(0, 18)) {
                        SetEntryFlag_020c1718(1, 18);
                        SetGlobalPackedBit_02027320(0x1164);
                    }
                    if (!IsGlobalPackedBitSet_02027304(0x1214) && IsGlobalPackedBitSet_02027304(0x1164)) {
                        SetEntryFlag_020c1718(2, 18);
                    }
                }
            }
            break;
        }
        case 2: {
            BitList36 bits = data_ov091_020c2960;
            int flagBit = bits.bits[id];
            BOOL unlocked = FALSE;
            if (index == 13) {
                if (ReadGlobalPackedBits_02027348(0x9f0, 7) == 100) {
                    unlocked = TRUE;
                }
            } else {
                unlocked = IsGlobalPackedBitSet_02027304(flagBit);
            }
            if (unlocked) {
                int slot = index - 28;
                switch (slot) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7: {
                    const FieldLimit *limit = &data_ov091_020c2ab8[slot];
                    if (ReadGlobalPackedBits_02027348(limit->offset, 17) > limit->max) {
                        unlocked = FALSE;
                    }
                    break;
                }
                }
            }
            entry->progress = unlocked;
            if (unlocked == data_ov091_020c2b3c[id]) {
                if (!IsEntryFlagSet_020c16e8(0, id)) {
                    SetEntryFlag_020c1718(1, id);
                    SetGlobalPackedBit_02027320(id + 0x1152);
                }
                if (!IsGlobalPackedBitSet_02027304(id + 0x1202) && IsGlobalPackedBitSet_02027304(id + 0x1152)) {
                    SetEntryFlag_020c1718(2, 0);
                }
            }
            break;
        }
        }
        if (record->hidden || record->id == -1 || IsEntryFlagSet_020c16e8(0, id) || IsEntryFlagSet_020c16e8(1, id)) {
            scene->entryCount++;
        }
    }
    countA = 0;
    countB = 0;
    for (i = 0; i < 30; i++) {
        if (IsEntryFlagSet_020c16e8(0, i)) {
            countA++;
        }
        if (IsEntryFlagSet_020c16e8(1, i)) {
            countB++;
        }
    }
    scene->unlockedTotal = countA + countB;
}
