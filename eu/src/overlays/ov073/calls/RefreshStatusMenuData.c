#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28c8];
    int heartCount;
    u32 experience;
    int munny;
    s8 levelBonus;
    u8 pad_28d5[2];
    u8 selectedRecord : 4;
    u8 selectedPage : 4;
    u8 pad_28d8[0x2c58 - 0x28d8];
    u32 equipMask;
    u8 pad_2c5c[6];
    u8 columnIndex;
    u8 pad_2c63[5];
    u8 extraRecords;
    u8 pad_2c69[0x2db8 - 0x2c69];
    u16 equippedIds[4];
} SaveData;

typedef struct StatBlock {
    u8 kind;
    u8 level;
    u16 hp;
    u16 maxHp;
    u16 attack;
    u16 defense;
    u16 magic;
    u16 capacity;
} StatBlock;

typedef struct StatPreview {
    u32 flags;
    s16 level;
    s16 maxHp;
    s16 attack;
    s16 defense;
    s16 magic;
    s16 capacity;
    int keepCurrent;
} StatPreview;

typedef struct StatText {
    u16 *labels[9];
    u16 level[2][4];
    u16 hp[2][10];
    u16 attack[2][4];
    u16 magic[2][4];
    u16 defense[2][4];
    u16 capacity[2][4];
    u16 *values[8][2];
    u16 experience[9];
    u16 nextLevel[9];
    u8 pad_100[0x1c];
    u16 changedMask;
    u16 decreasedMask;
    s16 levelBonus;
} StatText;

typedef struct RecordSlot {
    u32 iconId;
    u32 nameId;
    u8 state;
    u8 level;
    u8 kind;
    u8 pad_0b;
    u16 value;
    u16 pad_0e;
} RecordSlot;

typedef struct RecordList {
    u8 count;
    u8 pad_01[3];
    RecordSlot entries[14];
} RecordList;

typedef struct ProgressEntry {
    u32 id;
    u32 iconId;
    u32 nameId;
    u16 countText[8];
    BOOL complete;
} ProgressEntry;

typedef struct ProgressList {
    u16 count;
    u16 pad_02;
    ProgressEntry entries[64];
} ProgressList;

typedef struct ColumnBlock {
    u16 *title;
    u16 *labels[7];
    u16 *headers[4];
    u16 text[7][8];
    u16 *lines[8];
    u16 *details[8];
} ColumnBlock;

typedef struct Inventory {
    u8 pad_0000[0x24dc];
    s16 equipped[32];
    u8 pad_251c[0x32a8 - 0x251c];
    u16 stock[9];
} Inventory;

typedef struct StatusMenu {
    s8 page;
    u8 loaded;
    u8 pad_02;
    u8 flags;
    u16 digitBase;
    u16 numberBase;
    u8 pad_08[0xc];
    int busy;
    BOOL isCurrent;
    u8 pad_1c[0x10];
    StatText text;
    BOOL levelMaxed;
    BOOL maxHpMaxed;
    BOOL attackMaxed;
    BOOL defenseMaxed;
    BOOL magicMaxed;
    BOOL capacityMaxed;
    u8 pad_168[4];
    RecordList records;
    ProgressList progress;
    u8 pad_a54[8];
    ColumnBlock columns;
    u8 pad_b3c[0xdb4 - 0xb3c];
    Inventory *inventory;
    u8 pad_db8[0x10e0 - 0xdb8];
    void *container;
    u8 pad_10e4[0x10];
    s16 listCount;
    u8 pad_10f6[0x11d8 - 0x10f6];
    const char *countFormat;
} StatusMenu;

typedef struct MergedRecord {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} MergedRecord;

typedef struct BonusPair {
    int id;
    int amount;
} BonusPair;

typedef struct SlotPair0Entry {
    u8 pad_00[4];
    int type;
    int value;
    u8 pad_0c[0x14];
    BonusPair bonuses[4];
    u32 iconId;
    u32 nameId;
} SlotPair0Entry;

typedef struct SlotPair1Entry {
    u32 id;
    u8 pad_04[0x1c];
    u16 required;
    u8 pad_22[6];
    u32 iconId;
    u32 nameId;
} SlotPair1Entry;

extern SaveData *data_0205fe0c;
extern const char data_ov073_020c41d4[];
extern const char data_ov073_020c41ec[];
extern const char data_ov073_020c41f4[];
extern const char data_ov073_020c4208[];
extern const char data_ov073_020c4218[];
extern const char data_ov073_020c4228[];
extern const char data_ov073_020c4238[];
extern const char data_ov073_020c4244[];

extern StatusMenu *GetMenuSharedState(void);
extern int GetMenuSelection(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern u8 FindLevelForValue(u32 value, u32 *outRemaining);
extern s32 CheckStatusAndThreshold(void);
extern StatBlock *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern int OS_SNPrintf_0202e094(void *dst, u32 len, const char *fmt, ...);
extern void SetDigitDisplay(void *cells, int first, int value, void *origin);
extern void func_ov039_020be470(void *cells, int first, int value, void *origin);
extern BOOL ResolveMergedRecordEntry(int index, MergedRecord *entry, u32 *outValue);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern SlotPair1Entry *GetRecordSlotPair1Entry(s32 index);
extern void SetupStageParams(s16 *count, void *container, int refresh);
extern void GetRecordProgressInfo(StatusMenu *menu, int recordId, int count, ProgressEntry *info);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);
extern void qsort(void *base, int count, int size, int (*compare)(const void *, const void *));
extern int func_ov073_020c1ce0(const void *a, const void *b);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void LoadStatusLabels(StatusMenu *menu);
extern void SplitFxToTenths(int value, int *whole, int *tenths);
extern int ComputeScaledPercentPlusOne(void);
extern int ArmObject(void);
extern int ArmObject_02051180(void);
extern int GetDifficultyScale(void);
extern int GetFlagTableValue(void);
extern int CountUnlockedSlotsFx(void);
extern int HalveForEachFlag(void);
extern int _s32_div_f(int numerator, int denominator);

void RefreshStatusMenuData(SaveData *save, StatPreview *preview)
{
    StatusMenu *menu = GetMenuSharedState();
    RecordList *records;
    StatText *text;
    ProgressList *progress;
    ColumnBlock *columns;

    if (menu == NULL) {
        return;
    }
    records = &menu->records;
    text = &menu->text;
    progress = &menu->progress;
    columns = &menu->columns;
    menu->isCurrent = save == data_0205fe0c;
    if (save != NULL) {
        AcquireRecordSlot(0, 1);
        text->levelBonus = save->levelBonus;
        if (preview == NULL || (preview->flags & 1)) {
            int changed = 0;
            u32 remaining = 0;
            int decreased = 0;
            int scale;
            StatBlock stats;
            FindLevelForValue(save->experience, &remaining);
            scale = CheckStatusAndThreshold();
            stats = *GetOverlaySelectionRecord(0);
            OS_SNPrintf_0202e094(text->level[0], 4, data_ov073_020c41d4, stats.level + 1);
            OS_SNPrintf_0202e094(text->attack[0], 4, data_ov073_020c41d4, stats.attack);
            OS_SNPrintf_0202e094(text->magic[0], 4, data_ov073_020c41d4, stats.magic);
            OS_SNPrintf_0202e094(text->defense[0], 4, data_ov073_020c41d4, stats.defense);
            OS_SNPrintf_0202e094(text->capacity[0], 4, data_ov073_020c41d4, stats.capacity * scale);
            if (preview != NULL) {
                int levelDelta = preview->level - stats.level;
                int attackDelta = preview->attack - stats.attack;
                int magicDelta = preview->magic - stats.magic;
                int defenseDelta = preview->defense - stats.defense;
                int capacityDelta = (preview->capacity - stats.capacity) * scale;
                int row = preview->keepCurrent == 0;

                OS_SNPrintf_0202e094(text->level[row], 4, data_ov073_020c41d4, preview->level + 1);
                OS_SNPrintf_0202e094(text->attack[row], 4, data_ov073_020c41d4, preview->attack);
                OS_SNPrintf_0202e094(text->magic[row], 4, data_ov073_020c41d4, preview->magic);
                OS_SNPrintf_0202e094(text->defense[row], 4, data_ov073_020c41d4, preview->defense);
                OS_SNPrintf_0202e094(text->capacity[row], 4, data_ov073_020c41d4, preview->capacity * scale);
                if (preview->keepCurrent == 0) {
                    changed |= levelDelta != 0;
                    decreased |= levelDelta < 0;
                    changed |= (attackDelta != 0) << 2;
                    decreased |= (attackDelta < 0) << 2;
                    changed |= (defenseDelta != 0) << 3;
                    decreased |= (defenseDelta < 0) << 3;
                    changed |= (magicDelta != 0) << 4;
                    decreased |= (magicDelta < 0) << 4;
                    changed |= (capacityDelta != 0) << 5;
                    decreased |= (capacityDelta < 0) << 5;
                }
                menu->levelMaxed = preview->level + 1 >= 99;
                menu->maxHpMaxed = preview->maxHp >= 400;
                menu->attackMaxed = preview->attack >= 200;
                menu->defenseMaxed = preview->defense >= 200;
                menu->magicMaxed = preview->magic >= 200;
                menu->capacityMaxed = preview->capacity * scale >= 28;
            } else {
                text->level[1][0] = 0;
                text->attack[1][0] = 0;
                text->magic[1][0] = 0;
                text->defense[1][0] = 0;
                text->capacity[1][0] = 0;
                text->hp[1][0] = 0;
                menu->levelMaxed = stats.level + 1 >= 99;
                menu->maxHpMaxed = stats.maxHp >= 400;
                menu->attackMaxed = stats.attack >= 200;
                menu->defenseMaxed = stats.defense >= 200;
                menu->magicMaxed = stats.magic >= 200;
                menu->capacityMaxed = stats.capacity * scale >= 28;
            }
            if (preview != NULL && preview->maxHp != 0 && preview->maxHp != stats.maxHp && preview->keepCurrent == 0) {
                int hpDelta = preview->maxHp - stats.maxHp;

                changed |= (hpDelta != 0) << 1;
                decreased |= (hpDelta < 0) << 1;
                OS_SNPrintf_0202e094(text->hp[0], 4, data_ov073_020c41ec, stats.maxHp);
                OS_SNPrintf_0202e094(text->hp[1], 4, data_ov073_020c41ec, preview->maxHp);
            } else {
                u16 hp;

                if (GetMenuSelection() == 3) {
                    stats.hp = 0;
                }
                hp = stats.hp;
                if (hp == 0) {
                    hp = stats.maxHp;
                }
                OS_SNPrintf_0202e094(text->hp[0], 10, data_ov073_020c41f4, hp, stats.maxHp);
            }
            OS_SNPrintf_0202e094(text->experience, 9, data_ov073_020c41d4, save->experience);
            OS_SNPrintf_0202e094(text->nextLevel, 9, data_ov073_020c41d4, remaining);
            if (!menu->isCurrent || (menu->busy == 0 && (menu->flags & 2))) {
                SetDigitDisplay(menu->container, menu->digitBase, save->munny, NULL);
                func_ov039_020be470(menu->container, menu->numberBase, save->heartCount, NULL);
            }
            menu->text.changedMask = changed;
            menu->text.decreasedMask = decreased;
        }
        if (preview == NULL || (preview->flags & 1)) {
            int i;
            MergedRecord merged;
            u32 recordId;

            records->count = save->extraRecords + 3;
            for (i = 0; i < records->count; i++) {
                RecordSlot *slot = &records->entries[i];

                if (ResolveMergedRecordEntry(i, &merged, &recordId)) {
                    SlotPair0Entry *info = GetRecordSlotPair0Entry(recordId == -1 ? (u8)merged.category : recordId);

                    slot->iconId = info->iconId;
                    slot->nameId = info->nameId;
                    if (recordId == -1) {
                        slot->state = info->type != 3;
                        slot->level = merged.level;
                        slot->kind = merged.kind;
                        slot->value = info->value;
                    } else {
                        slot->state = 2;
                        slot->level = 0;
                        slot->kind = 0;
                        slot->value = 0;
                    }
                } else {
                    slot->iconId = 0;
                    slot->nameId = 0;
                }
            }
            if (menu->page == 1) {
                menu->listCount = records->count;
                SetupStageParams(&menu->listCount, menu->container, 1);
            }
            if (records->entries[data_0205fe0c->selectedRecord].iconId == 0) {
                for (i = 0; i < menu->listCount; i++) {
                    if (records->entries[i].iconId != 0) {
                        break;
                    }
                }
                if (i == menu->listCount) {
                    i = 15;
                }
                data_0205fe0c->selectedRecord = (u8)i;
                data_0205fe0c->selectedPage = 0;
            }
        }
        if (preview == NULL || (preview->flags & 4)) {
            int bonus[9] = {0};
            int count = 0;
            int equipSlot;
            SlotPair0Entry *item;
            int i;
            u32 mask;
            s16 *equipped;
            int bracerCount;
            int ringCount;
            int amuletCount;
            int beltCount;
            int crownCount;
            int chainCount;
            int charmCount;
            int gemCount;

            for (equipSlot = 0; equipSlot < 4; equipSlot++) {
                u16 itemId = data_0205fe0c->equippedIds[equipSlot];

                if (itemId != 0xffff) {
                    int j;

                    item = GetRecordSlotPair0Entry(itemId);
                    for (j = 0; j < 4; j++) {
                        int bonusId = item->bonuses[j].id;

                        if (bonusId != -1) {
                            if (bonusId >= 0 && bonusId < 9) {
                                bonus[bonusId] += item->bonuses[j].amount;
                            } else {
                                SlotPair1Entry *record = GetRecordSlotPair1Entry(bonusId);
                                ProgressEntry *entry = &progress->entries[count++];

                                entry->id = bonusId;
                                entry->iconId = record->iconId;
                                entry->nameId = record->nameId;
                                entry->countText[0] = 0;
                                entry->complete = FALSE;
                            }
                        }
                    }
                }
            }
            mask = data_0205fe0c->equipMask;
            equipped = menu->inventory->equipped;
            bracerCount = 0;
            ringCount = 0;
            amuletCount = 0;
            beltCount = 0;
            crownCount = 0;
            chainCount = 0;
            charmCount = 0;
            gemCount = 0;
            for (i = 0; i < 5; i++) {
                if (menu->inventory->stock[i] != 0) {
                    SlotPair1Entry *record = GetRecordSlotPair1Entry(i);
                    ProgressEntry *entry = &progress->entries[count++];
                    int amount = menu->inventory->stock[i] + bonus[i];

                    entry->complete = amount >= record->required;
                    if (entry->complete) {
                        amount = record->required;
                    }
                    entry->id = record->id;
                    entry->iconId = record->iconId;
                    entry->nameId = record->nameId;
                    OS_SNPrintf_0202e094(entry->countText, 7, menu->countFormat, amount);
                }
            }
            for (i = 0; i < 4; i++) {
                if (menu->inventory->stock[i + 5] != 0) {
                    SlotPair1Entry *record = GetRecordSlotPair1Entry(i + 5);
                    ProgressEntry *entry = &progress->entries[count++];
                    int amount = menu->inventory->stock[i + 5] + bonus[i + 5];

                    entry->complete = amount >= record->required;
                    if (entry->complete) {
                        amount = record->required;
                    }
                    entry->id = record->id;
                    entry->iconId = record->iconId;
                    entry->nameId = record->nameId;
                    OS_SNPrintf_0202e094(entry->countText, 7, menu->countFormat, amount);
                }
            }
            for (i = 0; i < 32; i++, equipped++) {
                if (*equipped >= 0 && (mask & (1 << i))) {
                    SlotPair1Entry *record = GetRecordSlotPair1Entry(*equipped);

                    switch (*(int *)record) {
                    case 0xf8:
                    case 0xf9:
                    case 0xfa:
                    case 0xfb:
                        bracerCount++;
                        break;
                    case 0xfc:
                    case 0xfd:
                        ringCount++;
                        break;
                    case 0xfe:
                    case 0xff:
                    case 0x100:
                        amuletCount++;
                        break;
                    case 0x101:
                    case 0x102:
                        beltCount++;
                        break;
                    case 0x103:
                    case 0x104:
                        crownCount++;
                        break;
                    case 0x105:
                    case 0x106:
                    case 0x107:
                        chainCount++;
                        break;
                    case 0x108:
                    case 0x109:
                    case 0x10a:
                        charmCount++;
                        break;
                    case 0x10b:
                    case 0x10c:
                        gemCount++;
                        break;
                    default: {
                        ProgressEntry *entry = &progress->entries[count];

                        entry->id = record->id;
                        entry->iconId = record->iconId;
                        count++;
                        entry->nameId = record->nameId;
                        entry->countText[0] = 0;
                        entry->complete = FALSE;
                        break;
                    }
                    }
                }
            }
            if (bracerCount) {
                GetRecordProgressInfo(menu, 9, bracerCount, &progress->entries[count++]);
            }
            if (ringCount) {
                GetRecordProgressInfo(menu, 10, ringCount, &progress->entries[count++]);
            }
            if (amuletCount) {
                GetRecordProgressInfo(menu, 13, amuletCount, &progress->entries[count++]);
            }
            if (beltCount) {
                GetRecordProgressInfo(menu, 14, beltCount, &progress->entries[count++]);
            }
            if (crownCount) {
                GetRecordProgressInfo(menu, 16, crownCount, &progress->entries[count++]);
            }
            if (chainCount) {
                GetRecordProgressInfo(menu, 18, chainCount, &progress->entries[count++]);
            }
            if (charmCount) {
                GetRecordProgressInfo(menu, 19, charmCount, &progress->entries[count++]);
            }
            if (gemCount) {
                GetRecordProgressInfo(menu, 20, gemCount, &progress->entries[count++]);
            }
            WriteGlobalPackedBits(0x1a0f, 3, bracerCount);
            progress->count = count;
            qsort(progress->entries, count, sizeof(ProgressEntry), func_ov073_020c1ce0);
            if (menu->page == 2) {
                menu->listCount = progress->count;
                SetupStageParams(&menu->listCount, menu->container, 1);
            }
        }
        if (preview == NULL || (preview->flags & 8)) {
            int whole;
            int tenths;
            int unlocked;
            int scaleBonus;

            columns->lines[0] = columns->headers[save->columnIndex];
            SplitFxToTenths(ComputeScaledPercentPlusOne(), &whole, &tenths);
            OS_SNPrintf_0202e094(columns->text[0], 8, data_ov073_020c4208, whole, tenths);
            SplitFxToTenths(ArmObject() * 100, &whole, &tenths);
            OS_SNPrintf_0202e094(columns->text[1], 8, data_ov073_020c4218, whole, tenths);
            SplitFxToTenths(GetDifficultyScale(), &whole, &tenths);
            OS_SNPrintf_0202e094(columns->text[2], 8, data_ov073_020c4208, whole, tenths);
            SplitFxToTenths(GetFlagTableValue(), &whole, &tenths);
            OS_SNPrintf_0202e094(columns->text[3], 8, data_ov073_020c4208, whole, tenths);
            unlocked = CountUnlockedSlotsFx();
            OS_SNPrintf_0202e094(columns->text[4], 8, data_ov073_020c4228, unlocked / 4096);
            scaleBonus = HalveForEachFlag();
            OS_SNPrintf_0202e094(columns->text[5], 8, scaleBonus == 0x1000 ? data_ov073_020c4238 : data_ov073_020c4244, _s32_div_f(0x1000, scaleBonus));
            SplitFxToTenths(ArmObject_02051180() * 100, &whole, &tenths);
            OS_SNPrintf_0202e094(columns->text[6], 8, data_ov073_020c4218, whole, tenths);
        }
        ReleaseRecordSlot(0);
    } else {
        MI_CpuFill8(text, 0, (u32)text->pad_100 - (u32)text);
        SetDigitDisplay(menu->container, menu->digitBase, 0, NULL);
        func_ov039_020be470(menu->container, menu->numberBase, 0, NULL);
        LoadStatusLabels(menu);
    }
    menu->loaded = 1;
}
