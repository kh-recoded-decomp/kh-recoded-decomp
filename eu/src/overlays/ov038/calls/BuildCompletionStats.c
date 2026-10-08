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

extern CompletionStats *data_ov038_020bd164;
extern SaveHeader *data_0205fe0c;
extern const int gResultsTopMessageIds[9][4];
extern const FieldIdTable gResultsMessageIds;
extern const RangeTable gResultsLayoutOffsets;
extern const RangeTable gResultsLayoutWidths;
extern const ProgressItem gResultsTopRecordTableA[0xef];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern u64 OS_GetTick(void);
extern s64 GetCardThreadStartTick(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern int CountSetBitsInMainFlagArray(void);
extern int GetUnlockedSlotValue(u32 index);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern int FindThresholdRank(int row, u32 value);

static inline int CountSetFlags(int bit, int total)
{
    int count = 0;
    int i;

    for (i = 0; i < total; i++, bit++) {
        if (IsGlobalPackedBitSet(bit)) {
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

    fieldIds = gResultsMessageIds;
    total = 0;

    for (i = 0; i < 5; i++) {
        total += ReadGlobalPackedBits(fieldIds.ids[i], 2);
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

    starts = gResultsLayoutOffsets;
    lengths = gResultsLayoutWidths;
    count = 0;

    for (i = 0; i < 8; i++) {
        bit = starts.values[i];
        length = lengths.values[i];

        for (j = 0; j < length; j++, bit++) {
            if (IsGlobalPackedBitSet(bit)) {
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
        int value = GetUnlockedSlotValue(i);
        if (value != -1) {
            slots[slotCount] = value;
            slotCount++;
        }
    }

    for (i = 0; i < 0xef; i++) {
        const ProgressItem *item = &gResultsTopRecordTableA[i];
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
        if (IsGlobalPackedBitSet(bit)) {
            count++;
        }
    }
    return count;
}

void BuildCompletionStats(void)
{
    CompletionStats *stats;
    int col;
    RankEntry *entry;
    int row;
    int count;
    int bit;
    int i;

    stats = NNSi_FndAllocFromDefaultHeap(sizeof(CompletionStats));
    data_ov038_020bd164 = stats;
    MI_CpuFill8(stats, 0, sizeof(CompletionStats));
    stats->bestCategory = 3;
    stats->playSeconds = data_0205fe0c->playSeconds +
        (((OS_GetTick() - GetCardThreadStartTick()) * 64) / 33514000);

    for (row = 0; row < 9; row++) {
        for (col = 0; col < 4; col++) {
            entry = &stats->ranks[row][col];
            entry->bits = ReadSessionPackedBits(gResultsTopMessageIds[row][col], 0x14);
            entry->rank = FindThresholdRank(row, entry->bits);
            if (entry->bits != 0) {
                stats->lastRanked[row] = col;
            }
        }
    }

    stats->bestCategory = FindBestCategory(stats) + 3;

    stats->percents[0] = CountSetFlags(0x9b0, 25) * 100 / 25;

    count = 0;
    for (i = 0, bit = 0x680; i < 40; i++, bit += 0x11) {
        if (ReadGlobalPackedBits(bit, 0x11)) {
            count++;
        }
    }
    stats->percents[1] = count * 100 / 40;
    stats->percents[2] = CountSetFlags(0xbd9, 11) * 100 / 11;
    stats->percents[3] = CountSetFlags(0xb59, 93) * 100 / 93;
    stats->percents[4] = SumFieldBits() * 100 / 15;
    stats->percents[5] = CountRangeFlags() * 100 / 111;
    stats->percents[6] = CountSetFlags(0x5c0, 0xc0) * 100 / 92;
    stats->percents[7] = CountSetBitsInMainFlagArray() * 100 / 815;
    stats->percents[8] = (int)ReadGlobalPackedBits(0xbf0, 8) * 100 / 200;
    stats->percents[9] = CountCollectedItems() * 100 / 0xef;
}
