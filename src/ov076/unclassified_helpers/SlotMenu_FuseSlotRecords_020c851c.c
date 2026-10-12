#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct RecordMerge {
    u16 targetIndex;
    u16 consumedIndex;
    RecordEntry result;
} RecordMerge;

typedef struct FuseRates {
    s32 rows[2][6];
} FuseRates;

typedef struct SlotMenu {
    u8 pad_00000[0x4d9e];
    u8 previewShown;
    u8 pad_04D9F[0x11ee6 - 0x4d9f];
    s16 slotIndex;
    u8 pad_11EE8[0x497f8 - 0x11ee8];
    RecordEntry slotRecords[8];
    u8 pad_49818[0x49860 - 0x49818];
    s32 resultType;
    s32 levelBonus;
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
    u8 ownedCategories[0x10];
} SaveData;

extern SaveData *data_0205fe0c;
extern const FuseRates data_ov076_020cd0c0;

extern RecordEntry *GetActiveRecordEntryOrNull_02029548(u16 index);
extern void SlotMenu_UnequipSlotEntry_020c89e0(SlotMenu *menu, int slot, int column);
extern int func_020293c4(RecordMerge *merge);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_ov076_020c82d8(SlotMenu *menu, int slot, int column, int recordIndex);
extern int nextRandom12_0202aa58(void);
extern void func_0202737c(int id, int kind, int delta, int limit);
extern void SetPackedBit(u8 *bits, int index);

static inline void MarkCategoryOwned(u8 category)
{
    SetPackedBit(data_0205fe0c->ownedCategories, category);
}
extern void SlotMenu_LockTouchUntilCommit_020c88dc(SlotMenu *menu, BOOL locked);

int SlotMenu_FuseSlotRecords_020c851c(SlotMenu *menu)
{
    FuseRates rates;
    RecordMerge merge;
    int rowOffset;
    int same;
    int fusedIndex;
    u16 levelSum;
    int result;
    const s32 *row;
    int chance;
    int targetIndex;
    int consumedIndex;
    BOOL complete;
    BOOL maxed;
    int slot;
    u16 consumedHandle;
    RecordEntry *target;
    RecordEntry *consumed;
    RecordEntry *fused;
    int kind;
    int level;
    int roll;

    slot = menu->slotIndex;
    consumedHandle = data_0205fe0c->slotHandles[slot * 2 + 1];
    result = 0;
    targetIndex = data_0205fe0c->slotHandles[slot * 2] - 0x200;
    target = GetActiveRecordEntryOrNull_02029548(targetIndex);
    consumedIndex = consumedHandle - 0x200;
    consumed = GetActiveRecordEntryOrNull_02029548(consumedIndex);
    levelSum = target->level + consumed->level;
    complete = (target->kind | consumed->kind) == 3 ? TRUE : FALSE;
    SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, 0);
    SlotMenu_UnequipSlotEntry_020c89e0(menu, slot, 1);
    merge.targetIndex = targetIndex;
    merge.consumedIndex = consumedIndex;
    merge.result = menu->slotRecords[slot];
    fusedIndex = func_020293c4(&merge);
    SetGlobalPackedBit_02027320((u8)merge.result.category);
    menu->previewShown = 0;
    func_ov076_020c82d8(menu, slot, 0, fusedIndex);
    fused = GetActiveRecordEntryOrNull_02029548(fusedIndex);
    maxed = complete && fused->level >= 100;
    rates = data_ov076_020cd0c0;
    same = target->category == consumed->category ? 1 : 0;
    rowOffset = same * sizeof(rates.rows[0]);
    row = (const s32 *)((u8 *)&rates + rowOffset);
    kind = fused->kind;
    level = fused->level;
    chance = row[0] + (levelSum << 12) / 10;
    menu->resultType = 0;
    while (!maxed) {
        if (nextRandom12_0202aa58() * 100 <= chance) {
            if (!(kind & 1)) {
                fused->kind |= 1;
                result = 1;
                menu->resultType = fused->kind;
            } else if (!(kind & 2)) {
                fused->kind |= 2;
                result = 1;
                menu->resultType = fused->kind;
            }
        }
        if (nextRandom12_0202aa58() * 100 <= chance) {
            if (!(kind & 2)) {
                fused->kind |= 2;
                result = 1;
                menu->resultType = fused->kind;
            } else if (!(kind & 1)) {
                fused->kind |= 1;
                result = 1;
                menu->resultType = fused->kind;
            }
        }
        if (result == 0) {
            if (level == 100) {
                if ((kind & 1) && (kind & 2)) {
                    maxed = TRUE;
                    break;
                }
            } else if (nextRandom12_0202aa58() * 100 <= row[1]) {
                menu->levelBonus = 10;
                result = 1;
                level += 10;
                menu->resultType = 4;
                break;
            }
            roll = nextRandom12_0202aa58() * 100;
            if (roll <= row[2]) {
                level += 5;
                menu->levelBonus = 5;
                menu->resultType = 5;
            } else if ((roll -= row[2]) <= row[3]) {
                menu->levelBonus = 4;
                level += 4;
                menu->resultType = 6;
            } else if ((roll -= row[3]) <= row[4]) {
                menu->levelBonus = 3;
                level += 3;
                menu->resultType = 7;
            } else if ((roll -= row[4]) <= row[5]) {
                menu->levelBonus = 2;
                level += 2;
                menu->resultType = 8;
            } else {
                menu->levelBonus = 1;
                level += 1;
                menu->resultType = 9;
            }
        }
        break;
    }
    if (maxed) {
        menu->resultType = 0;
    }
    if (level > 100 && menu->levelBonus != 0) {
        menu->levelBonus = 100 - fused->level;
    }
    if (level >= 100) {
        level = 100;
    }
    fused->level = level;
    func_0202737c(0xb04, 0x11, 1, 99999);
    if (fused->kind == 3) {
        SetGlobalPackedBit_02027320(fused->category + 0xb59);
    }
    if (fused->level >= 100) {
        SetGlobalPackedBit_02027320(0xbe8);
        if (fused->kind == 3) {
            SetGlobalPackedBit_02027320(0xbe9);
        }
    }
    MarkCategoryOwned(fused->category);
    SlotMenu_LockTouchUntilCommit_020c88dc(menu, TRUE);
    return result;
}
