#include "nitro/types.h"

typedef struct UnitStats {
    u8 kind;
    u8 level;
    u16 hp;
    u16 maxHp;
    u16 attack;
    u16 defense;
    u16 magic;
    u16 capacity;
} UnitStats;

typedef struct StatPreview {
    u32 flags;
    s16 level;
    s16 maxHp;
    s16 attack;
    s16 defense;
    s16 magic;
    s16 capacity;
    int keepCurrent;
    int reserved;
} StatPreview;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 pad_bits : 13;
    u32 refillHp : 1;
} FieldState;

typedef struct MatrixMenu MatrixMenu;
typedef struct BonusRecord BonusRecord;

extern void *data_0205fe0c;
extern FieldState *data_ov001_020a0460;
extern const StatPreview data_ov075_020d1530;

extern UnitStats *func_02051124(void);
extern BonusRecord *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern void ComputePlayerStats_02050b30(void *state, UnitStats *out, BOOL recompute, int scaleParam);
extern void DrawNodeGroupRecords_020c5c58(MatrixMenu *menu, UnitStats *stats, int defaultIndex);
extern void ApplyLinkedGroupBonuses_020c5ca8(MatrixMenu *menu, UnitStats *stats);
extern void RevertLevelBonus_020c5c04(UnitStats *stats, BonusRecord *bonus, u8 count);
extern void ApplyLevelBonus_020c5bb0(UnitStats *stats, BonusRecord *bonus, u8 count);
extern void ScaleStatsByPercent_02050a80(UnitStats *stats, BOOL useOverlay);
extern void LoadLevelStats_0204f804(u32 level, UnitStats *stats);
extern int ArmObject_0205115c(void);
extern UnitStats *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern int GetFieldCad0_020bcb00(void);
extern void RefreshStatusMenuData_020c1eb4(void *save, StatPreview *preview);

void PreviewMatrixNodeStats_020c5d10(MatrixMenu *menu, int oldIndex, int newIndex, u32 mode)
{
    UnitStats levelStats = {0};
    UnitStats stats;
    StatPreview preview;
    UnitStats computed;
    UnitStats applied;
    UnitStats *base;
    BonusRecord *record;
    int isPreview;
    int scale;
    int fraction;
    UnitStats *selection;

    base = func_02051124();
    preview = data_ov075_020d1530;
    record = GetRecordSlotPair0Entry_02051ec8(oldIndex);
    isPreview = mode & 2;
    if (!isPreview) {
        preview.keepCurrent = (mode & 0x18) != 0;
        if (!preview.keepCurrent) {
            ComputePlayerStats_02050b30(data_0205fe0c, &computed, TRUE, 0);
            stats = *base;
        } else if (mode & 4) {
            stats = *base;
            DrawNodeGroupRecords_020c5c58(menu, &stats, newIndex);
        } else if (mode & 8) {
            stats = *base;
            ApplyLinkedGroupBonuses_020c5ca8(menu, &stats);
        } else {
            stats = *base;
        }
    } else {
        stats = *base;
        if (mode & 4) {
            DrawNodeGroupRecords_020c5c58(menu, &stats, newIndex);
        } else if (mode & 8) {
            ApplyLinkedGroupBonuses_020c5ca8(menu, &stats);
        } else {
            if (record != NULL) {
                RevertLevelBonus_020c5c04(&stats, record, (mode & 1 ? 1 : 0) + 1);
            }
            record = GetRecordSlotPair0Entry_02051ec8(newIndex);
            if (record != NULL) {
                ApplyLevelBonus_020c5bb0(&stats, record, (mode & 1 ? 1 : 0) + 1);
            }
        }
    }
    ScaleStatsByPercent_02050a80(&stats, FALSE);
    LoadLevelStats_0204f804(stats.level, &levelStats);
    preview.level = stats.level;
    preview.maxHp = stats.maxHp + levelStats.maxHp;
    preview.attack = stats.attack + levelStats.attack;
    preview.defense = stats.defense + levelStats.defense;
    preview.magic = stats.magic + levelStats.magic;
    preview.capacity = stats.capacity + levelStats.capacity;
    if (preview.level > 98) {
        preview.level = 98;
    }
    if (preview.maxHp > 400) {
        preview.maxHp = 400;
    }
    if (preview.attack > 200) {
        preview.attack = 200;
    }
    if (preview.defense > 200) {
        preview.defense = 200;
    }
    if (preview.magic > 200) {
        preview.magic = 200;
    }
    if (preview.capacity > 28) {
        preview.capacity = 28;
    }
    scale = ArmObject_0205115c();
    fraction = (scale & 0xfff) * 1000 / 4096;
    if (fraction % 10 >= 5) {
        fraction += 10 - fraction % 10;
    }
    fraction += scale / 4096 * 1000;
    preview.maxHp = preview.maxHp * fraction / 1000;
    if (preview.maxHp == 0) {
        preview.maxHp = 1;
    }
    if (isPreview) {
        RefreshStatusMenuData_020c1eb4(data_0205fe0c, &preview);
        return;
    }
    selection = GetOverlaySelectionRecord(0);
    preview.flags = -1;
    selection->level = preview.level;
    selection->maxHp = preview.maxHp;
    if (GetFieldCad0_020bcb00() != 0 || data_ov001_020a0460->refillHp) {
        selection->hp = selection->maxHp;
    } else if (selection->maxHp < selection->hp) {
        selection->hp = selection->maxHp;
    }
    selection->attack = preview.attack;
    selection->defense = preview.defense;
    selection->magic = preview.magic;
    selection->capacity = preview.capacity;
    ComputePlayerStats_02050b30(data_0205fe0c, &applied, FALSE, 0);
    RefreshStatusMenuData_020c1eb4(data_0205fe0c, &preview);
}
