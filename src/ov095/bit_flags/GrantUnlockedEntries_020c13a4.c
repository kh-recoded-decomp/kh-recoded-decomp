#include "nitro/types.h"

typedef struct {
    int type;
    int value;
} UnlockEntry;

typedef struct {
    u8 pad_00000[0x11150];
    int newFlags[0xef];
} UnlockScene;

extern UnlockEntry data_ov095_020c1998[];
extern int data_ov095_020c1788[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern int GetUnlockedSlotValue_02051270(u32 index);
extern void SetEntryFlag_020c1354(int useSecondSet, int bitIndex);

void GrantUnlockedEntries_020c13a4(UnlockScene *scene)
{
    int idCount = 0;
    int counts[9] = {0};
    int ids[32];
    int i;
    int j;
    int value;

    for (i = 0; i < 32; i++) {
        value = GetUnlockedSlotValue_02051270(i);
        if (value != -1) {
            ids[idCount++] = value;
        }
    }

    for (i = 0; i < 0xef; i++) {
        UnlockEntry *entry = &data_ov095_020c1998[i];
        switch (entry->type) {
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (IsGlobalPackedBitSet_02027304(entry->value)) {
                SetEntryFlag_020c1354(0, i);
                counts[entry->type]++;
            }
            if ((u32)(entry->type - 3) <= 1 && IsGlobalPackedBitSet_02027304(entry->value + 0xb59)) {
                scene->newFlags[i] = 1;
            }
            break;
        case 1:
            for (j = 0; j < idCount; j++) {
                if (entry->value == ids[j]) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                    break;
                }
            }
            break;
        case 2:
            switch (entry->value) {
            case 6:
                if (IsGlobalPackedBitSet_02027304(0xbeb)) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                }
                break;
            case 8:
                if (IsGlobalPackedBitSet_02027304(0xbec)) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                }
                break;
            case 10:
                if (IsGlobalPackedBitSet_02027304(0xbed)) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                }
                break;
            case 12:
                if (IsGlobalPackedBitSet_02027304(0xbee)) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                }
                break;
            case 14:
                if (IsGlobalPackedBitSet_02027304(0xbef)) {
                    SetEntryFlag_020c1354(0, i);
                    counts[entry->type]++;
                }
                break;
            }
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        if (counts[i] == data_ov095_020c1788[i]) {
            SetEntryFlag_020c1354(1, i);
        }
    }
}


