#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PlayerStats {
    u8 unk_0;
    u8 level;
    u16 unk_2;
    u16 hp;
    u16 strength;
    u16 magic;
    u16 defense;
    u16 unk_C;
} PlayerStats;

typedef struct MapCell {
    u16 cell;
    u8 type;
    s8 link;
    s16 param;
    u16 group;
} MapCell;

typedef struct MapFile {
    u8 pad_00[4];
    u16 cellCount;
} MapFile;

typedef struct MapLayout {
    u8 pad_0000[0x9c];
    MapFile *file;
    u8 pad_00A0[0x1b00];
    MapCell *cellList[0x190];
    u8 pad_21E0[0x10cc];
    u16 chipCountsA[5];
    u16 chipCountsB[4];
    u8 pad_32BE[2];
    PlayerStats bonusStats;
    PlayerStats finalStats;
} MapLayout;

typedef struct ChipEntry {
    u8 pad_00[0x1a];
    u8 levelBonus;
    s8 hpBonus;
    s8 strengthBonus;
    s8 magicBonus;
    s8 defenseBonus;
    s8 unkBonus_1F;
    s32 kind;
    s32 amount;
} ChipEntry;

typedef struct GameState {
    u8 pad_0000[0x28d4];
    s8 mode;
    u8 pad_28D5[0x38b];
    u16 activeGroupMask;
} GameState;

extern MapLayout *data_020613cc;
extern GameState *data_0205fe0c;

extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern ChipEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void GetBaseStatsForLevel_0204f804(u32 level, PlayerStats *stats);
extern void ScaleStatsByPercent_02050a80(PlayerStats *stats, int param);
extern fx32 MultiplyTwoPercentFractions_02050698(GameState *state);
extern s64 func_02023dbc(s32 numerator, s32 denominator);

void ComputePlayerStats_02050b30(GameState *state, PlayerStats *out, BOOL recompute, int scaleParam)
{
    MapLayout *map = data_020613cc;
    PlayerStats bonus = {0};
    PlayerStats base;
    fx32 factor;
    int fraction;
    int remainder;

    if (recompute) {
        int remaining;
        MapCell **list;
        u32 mask;

        mask = state->activeGroupMask;
        list = map->cellList;

        OpenRecordManager_02051c80();
        AcquireRecordSlot_02051d3c(0, 1);
        func_01ff88c4(map->chipCountsA, 0, sizeof(map->chipCountsA));
        func_01ff88c4(map->chipCountsB, 0, sizeof(map->chipCountsB));
        for (remaining = map->file->cellCount; remaining > 0; remaining--, list++) {
            MapCell *cell = *list;
            if ((cell->type == 1 || cell->type == 2) && cell->param >= 0) {
                ChipEntry *entry = GetRecordSlotPair0Entry_02051ec8(cell->param);
                int count;
                int kind;

                if (cell->type == 1 && (mask & (1 << cell->group))) {
                    count = 2;
                } else {
                    count = 1;
                }
                kind = entry->kind;
                if (kind < 0) {
                    do {
                        bonus.level += entry->levelBonus;
                        bonus.hp += entry->hpBonus;
                        bonus.strength += entry->strengthBonus;
                        bonus.magic += entry->magicBonus;
                        bonus.defense += entry->defenseBonus;
                        bonus.unk_C += entry->unkBonus_1F;
                    } while (--count);
                } else if (kind >= 0 && kind <= 4) {
                    do {
                        map->chipCountsA[kind] += (u16)entry->amount;
                    } while (--count);
                } else if (kind >= 5 && kind <= 8) {
                    do {
                        map->chipCountsB[kind - 5] += (u16)entry->amount;
                    } while (--count);
                }
            }
        }
        map->bonusStats = bonus;
        ReleaseRecordSlot_02051dfc(0);
        CloseRecordManager_02051cdc();
    } else {
        bonus = map->bonusStats;
    }

    if (bonus.level > 98) {
        bonus.level = 98;
    }
    GetBaseStatsForLevel_0204f804(bonus.level, &base);
    map->finalStats.unk_0 = 0;
    map->finalStats.level = bonus.level;
    map->finalStats.hp = bonus.hp + base.hp;
    map->finalStats.strength = bonus.strength + base.strength;
    map->finalStats.magic = bonus.magic + base.magic;
    map->finalStats.defense = bonus.defense + base.defense;
    map->finalStats.unk_C = bonus.unk_C + base.unk_C;
    if (map->finalStats.hp > 400) {
        map->finalStats.hp = 400;
    }
    if (map->finalStats.strength > 200) {
        map->finalStats.strength = 200;
    }
    if (map->finalStats.magic > 200) {
        map->finalStats.magic = 200;
    }
    if (map->finalStats.defense > 200) {
        map->finalStats.defense = 200;
    }
    if (map->finalStats.unk_C > 28) {
        map->finalStats.unk_C = 28;
    }

    if (data_0205fe0c->mode == 6) {
        ScaleStatsByPercent_02050a80(&bonus, scaleParam);
        GetBaseStatsForLevel_0204f804(bonus.level, &base);
        out->unk_0 = 0;
        out->level = bonus.level;
        out->hp = bonus.hp + base.hp;
        out->strength = bonus.strength + base.strength;
        out->magic = bonus.magic + base.magic;
        out->defense = bonus.defense + base.defense;
        out->unk_C = bonus.unk_C + base.unk_C;
        if (out->level > 98) {
            out->level = 98;
        }
        if (out->hp > 400) {
            out->hp = 400;
        }
        if (out->strength > 200) {
            out->strength = 200;
        }
        if (out->magic > 200) {
            out->magic = 200;
        }
        if (out->defense > 200) {
            out->defense = 200;
        }
        if (out->unk_C > 28) {
            out->unk_C = 28;
        }
    } else {
        u16 saved = out->unk_2;
        *out = map->finalStats;
        out->unk_2 = saved;
    }

    factor = MultiplyTwoPercentFractions_02050698(state);
    fraction = (int)((factor & 0xfff) * 1000) / 4096;
    remainder = (s32)(func_02023dbc(fraction, 10) >> 32);
    if (remainder >= 5) {
        fraction += 10 - remainder;
    }
    fraction += (factor / 4096) * 1000;
    out->hp = (s32)func_02023dbc(out->hp * fraction, 1000);
    if (out->hp == 0) {
        out->hp = 1;
    }
}
