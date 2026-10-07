#include "nitro/types.h"

typedef struct {
    int rank;
    u32 bits;
} RankEntry;

typedef struct {
    int type;
    int value;
} ProgressItem;

typedef struct {
    int ids[5];
} FieldIdTable;

typedef struct {
    u32 values[8];
} RangeTable;

typedef struct {
    u8 pad_0000[0xd0b0];
    int percents[10];
    RankEntry ranks[9][4];
    int lastRanked[9];
    int bestCategory;
    u32 playSeconds;
} CompletionStats;

typedef struct {
    u8 pad_0000[0x28c8];
    u32 playSeconds;
} SaveHeader;

extern CompletionStats *data_ov038_020bd144;
extern SaveHeader *data_0205fe0c;
extern const int data_ov038_020bbe4c[9][4];
extern const FieldIdTable data_ov038_020bbd10;
extern const RangeTable data_ov038_020bbd58;
extern const RangeTable data_ov038_020bbd38;
extern const ProgressItem data_ov038_020bbedc[0xef];

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, int size);
extern u64 OS_GetTick_02003fd4(void);
extern s64 GetCardThreadStartTick_0202726c(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern int func_020275e4(void);
extern int GetUnlockedSlotValue_02051270(u32 index);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern int FindThresholdRank_0207ebf4(int row, u32 value);

static inline int CountSetFlags(int bit, int total)
{
    int count = 0;
    int i;

    for (i = 0; i < total; i++, bit++) {
        if (IsGlobalPackedBitSet_02027304(bit)) {
            count++;
        }
    }
    return count;
}

static inline int FindBestCategory(CompletionStats *stats)
{
    int i;
    int bestIndex;
    int best;
    int bests[3] = {0, 0, 0};

    best = 0;
    bestIndex = 0;
    for (i = 0; i < 3; i++) {
        bests[i] = stats->ranks[i + 3][stats->lastRanked[i + 3]].bits;
    }
    for (i = 0; i < 3; i++) {
        if (bests[i] >= best) {
            bestIndex = i;
            best = bests[i];
        }
    }
    return bestIndex;
}

static inline int SumFieldBits(void)
{
    int i;
    int total;
    FieldIdTable fieldIds;

    fieldIds = data_ov038_020bbd10;
    total = 0;

    for (i = 0; i < 5; i++) {
        total += ReadGlobalPackedBits_02027348(fieldIds.ids[i], 2);
    }
    return total;
}

static inline int CountRangeFlags(void)
{
    int i;
    u32 length;
    u32 j;
    int bit;
    int count;
    RangeTable lengths;
    RangeTable starts;

    starts = data_ov038_020bbd58;
    lengths = data_ov038_020bbd38;
    count = 0;

    for (i = 0; i < 8; i++) {
        bit = starts.values[i];
        length = lengths.values[i];

        for (j = 0; j < length; j++, bit++) {
            if (IsGlobalPackedBitSet_02027304(bit)) {
                count++;
            }
        }
    }
    return count;
}

static inline int CountCollectedItems(void)
{
    int j;
    int bit;
    int i;
    int count;
    int slotCount;
    int slots[32];

    slotCount = 0;
    count = 0;

    for (i = 0; i < 32; i++) {
        int value = GetUnlockedSlotValue_02051270(i);
        if (value != -1) {
            slots[slotCount] = value;
            slotCount++;
        }
    }

    for (i = 0; i < 0xef; i++) {
        const ProgressItem *item = &data_ov038_020bbedc[i];
        switch (item->type) {
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            bit = item->value;
            break;
        case 1:
            for (j = 0; j < slotCount; j++) {
                if (item->value == slots[j]) {
                    count++;
                    break;
                }
            }
            continue;
        case 2:
            switch (item->value) {
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
    return count;
}

void BuildCompletionStats_020bb674(void)
{
    CompletionStats *stats;
    int col;
    RankEntry *entry;
    int row;
    int count;
    int bit;
    int i;

    stats = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(CompletionStats));
    data_ov038_020bd144 = stats;
    func_01ff8830(stats, 0, sizeof(CompletionStats));
    stats->bestCategory = 3;
    stats->playSeconds = data_0205fe0c->playSeconds +
        (((OS_GetTick_02003fd4() - GetCardThreadStartTick_0202726c()) * 64) / 33514000);

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 4; col++) {
            entry = &stats->ranks[row][col];
            entry->bits = ReadSessionPackedBits_02064574(data_ov038_020bbe4c[row][col], 0x14);
            entry->rank = FindThresholdRank_0207ebf4(row, entry->bits);
            if (entry->bits != 0) {
                stats->lastRanked[row] = col;
            }
        }
    }

    stats->bestCategory = FindBestCategory(stats) + 3;

    stats->percents[0] = CountSetFlags(0x9b0, 25) * 100 / 25;

    count = 0;
    for (i = 0, bit = 0x680; i < 40; i++, bit += 0x11) {
        if (ReadGlobalPackedBits_02027348(bit, 0x11)) {
            count++;
        }
    }
    stats->percents[1] = count * 100 / 40;
    stats->percents[2] = CountSetFlags(0xbd9, 11) * 100 / 11;
    stats->percents[3] = CountSetFlags(0xb59, 93) * 100 / 93;
    stats->percents[4] = SumFieldBits() * 100 / 15;
    stats->percents[5] = CountRangeFlags() * 100 / 111;
    stats->percents[6] = CountSetFlags(0x5c0, 0xc0) * 100 / 92;
    stats->percents[7] = func_020275e4() * 100 / 815;
    stats->percents[8] = (int)ReadGlobalPackedBits_02027348(0xbf0, 8) * 100 / 200;
    stats->percents[9] = CountCollectedItems() * 100 / 0xef;
}
