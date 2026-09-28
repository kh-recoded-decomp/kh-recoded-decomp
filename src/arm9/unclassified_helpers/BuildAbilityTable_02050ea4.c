#include "nitro/types.h"

typedef struct TaggedEntryTable TaggedEntryTable;

typedef struct MapLayout {
    u8 pad_0000[0x24e0];
    s16 chipIds[32];
    u8 pad_2520[0xd8c];
    u16 chipCountsA[5];
    u16 chipCountsB[4];
} MapLayout;

typedef struct GameState {
    u8 pad_0000[0x2c58];
    u32 activeChipMask;
    u8 pad_2C5C[0xe];
    u8 hasPartyAbilities;
    u8 pad_2C6B[0x14d];
    u16 partySlots[4];
} GameState;

typedef struct ChipRecord {
    u32 kind;
} ChipRecord;

typedef struct AbilitySlot {
    s32 abilityId;
    s32 unk_4;
} AbilitySlot;

typedef struct PartyRecord {
    u8 pad_00[0x20];
    AbilitySlot abilities[4];
} PartyRecord;

extern GameState *data_0205fe0c;
extern MapLayout *data_020613cc;

extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern PartyRecord *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern ChipRecord *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern void ClearTaggedEntryTable_0204fdc8(TaggedEntryTable *table);
extern void *AddTaggedEntry_0204fe2c(TaggedEntryTable *table, u32 id, int flag, u32 value);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void BuildAbilityTable_02050ea4(TaggedEntryTable *table)
{
    u32 mask = data_0205fe0c->activeChipMask;
    MapLayout *map = data_020613cc;
    u32 countA = 0;
    u32 countB = 0;
    u32 countC = 0;
    u32 countD = 0;
    u32 countE = 0;
    u32 countF = 0;
    u32 countG = 0;
    u32 countH = 0;
    s16 *chipIds;
    int i;
    int slot;

    OpenRecordManager_02051c80();
    chipIds = map->chipIds;
    ClearTaggedEntryTable_0204fdc8(table);
    for (i = 0; i < 5; i++) {
        u32 count = map->chipCountsA[i];
        if (count != 0) {
            if (count >= 100) {
                count = 100;
            }
            AddTaggedEntry_0204fe2c(table, i, 1, count);
        }
    }
    for (i = 0; i < 4; i++) {
        u32 count = map->chipCountsB[i];
        if (count != 0) {
            if (count >= 100) {
                count = 100;
            }
            AddTaggedEntry_0204fe2c(table, i + 5, 1, count);
        }
    }

    if (mask != 0) {
        AcquireRecordSlot_02051d3c(1, 1);
        for (i = 0; i < 32; i++, chipIds++) {
            if (*chipIds >= 0 && (mask & (1 << i))) {
                switch (GetRecordSlotPair1Entry_02051ef4(*chipIds)->kind) {
                case 0xf8:
                case 0xf9:
                case 0xfa:
                case 0xfb:
                    countA++;
                    break;
                case 0xfc:
                case 0xfd:
                    countB++;
                    break;
                case 0xfe:
                case 0xff:
                case 0x100:
                    countC++;
                    break;
                case 0x101:
                case 0x102:
                    countD++;
                    break;
                case 0x103:
                case 0x104:
                    countE++;
                    break;
                case 0x105:
                case 0x106:
                case 0x107:
                    countF++;
                    break;
                case 0x108:
                case 0x109:
                case 0x10a:
                    countG++;
                    break;
                case 0x10b:
                case 0x10c:
                    countH++;
                    break;
                default:
                    AddTaggedEntry_0204fe2c(table, *chipIds, 1, 1);
                    break;
                }
            }
        }
        if (countA != 0) {
            AddTaggedEntry_0204fe2c(table, 9, 1, countA);
        }
        if (countB != 0) {
            AddTaggedEntry_0204fe2c(table, 10, 1, countB);
        }
        if (countC != 0) {
            AddTaggedEntry_0204fe2c(table, 13, 1, countC);
        }
        if (countD != 0) {
            AddTaggedEntry_0204fe2c(table, 14, 1, countD);
        }
        if (countE != 0) {
            AddTaggedEntry_0204fe2c(table, 16, 1, countE);
        }
        if (countF != 0) {
            AddTaggedEntry_0204fe2c(table, 18, 1, countF);
        }
        if (countG != 0) {
            AddTaggedEntry_0204fe2c(table, 19, 1, countG);
        }
        if (countH != 0) {
            AddTaggedEntry_0204fe2c(table, 20, 1, countH);
        }
        WriteGlobalPackedBits_02027360(0x1a0f, 3, countA);
        ReleaseRecordSlot_02051dfc(1);
    }

    if (data_0205fe0c->partySlots[0] != 0xffff || data_0205fe0c->hasPartyAbilities) {
        slot = 0;
        AcquireRecordSlot_02051d3c(0, 1);
        do {
            if (data_0205fe0c->partySlots[slot] != 0xffff) {
                PartyRecord *record = GetRecordSlotPair0Entry_02051ec8(data_0205fe0c->partySlots[slot]);
                int k;
                for (k = 0; k < 4; k++) {
                    if (record->abilities[k].abilityId != -1) {
                        AddTaggedEntry_0204fe2c(table, record->abilities[k].abilityId, 1, 1);
                    }
                }
            }
            slot++;
        } while (slot < 4);
        ReleaseRecordSlot_02051dfc(0);
    }
    CloseRecordManager_02051cdc();
}
