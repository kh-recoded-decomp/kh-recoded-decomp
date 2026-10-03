#include "nitro/types.h"

typedef struct SessionState {
    u32 stageId;
    u8 pad_04[2];
    u16 mode : 3;
    u16 unk_3 : 2;
    u16 variant : 3;
    u16 layoutIndex : 5;
    u16 hasBonus : 1;
    u16 unk_14 : 2;
    u8 level;
    u8 floorCount;
    u8 pad_0a[2];
    u32 seed;
} SessionState;

typedef struct StageEntry {
    s8 kind;
    u8 pad_01;
    u16 values[3];
    s8 enemySet;
    u8 pad_09;
    s16 enemyLevel;
    u8 musicA;
    u8 musicB;
    u8 backdrop;
    u8 lighting;
    u8 layout;
    u8 pad_11;
    u16 mapId;
    u8 timeLimit;
    u8 pad_15[3];
    u32 rules;
    s8 bonusA;
    s8 bonusB;
    u8 bonusC;
    s8 bonusD;
    s8 bonusE;
    u8 effectA;
    u8 effectB;
    u8 effectC;
    u8 rewardSet;
    u8 bonusChance;
    u8 pad_26[2];
} StageEntry;

typedef struct LayoutEntry {
    u16 mapId;
    u16 layout;
} LayoutEntry;

typedef struct RewardPair {
    u16 item;
    u16 count;
} RewardPair;

typedef struct RewardRow {
    RewardPair pairs[4];
} RewardRow;

typedef struct StageParams {
    u32 stageId;
    u8 pad_04[4];
    u32 rules;
    u16 mapId;
    u16 timeLimit;
    u16 progress;
    s16 enemyLevel;
    u16 rewardCounts[4];
    u16 colors[3];
    u8 pad_22;
    u8 cleared;
    u8 level;
    u8 floorCount;
    s8 layout;
    u8 pad_27[8];
    u8 musicA;
    u8 musicB;
    u8 pad_31[0x2d];
    u8 backdrop;
    u8 pad_5f[2];
    u8 lighting;
    u8 pad_62;
    u8 effectA;
    u8 effectB;
    u8 effectC;
    u8 values[3];
    s8 bonusA;
    s8 bonusB;
    u8 bonusC;
    s8 bonusD;
    s8 bonusE;
    s8 enemySet;
    u8 pad_6f;
    u8 rewardItems[4];
    u8 pad_74[4];
    int timer;
    int active;
    u8 pad_80[8];
    int retries;
    int bonusRolled;
} StageParams;

extern SessionState data_0206085c;
extern StageEntry data_ov034_020bf970[];
extern LayoutEntry data_ov034_020be9d8[];
extern u8 data_ov034_020bea58[][3];
extern RewardRow data_ov034_020beb0c[];

extern void SeedSharedRandomState_0202a984(u32 seedLow, u32 seedHigh, u32 extra);
extern int func_0202a9d0(int range);

static inline void CopyStageEntry(StageParams *params, StageEntry *src)
{
    params->enemySet = src->enemySet;
    params->enemyLevel = src->enemyLevel;
    params->musicA = src->musicA;
    params->musicB = src->musicB;
    params->backdrop = src->backdrop;
    params->lighting = src->lighting;
    params->rules = src->rules;
    params->bonusA = src->bonusA;
    params->bonusB = src->bonusB;
    params->bonusC = src->bonusC;
    params->bonusD = src->bonusD;
    params->bonusE = src->bonusE;
    params->effectA = src->effectA;
    params->effectB = src->effectB;
    params->effectC = src->effectC;
}

static inline int RollStageBonus(StageEntry *entry)
{
    return entry->bonusChance > func_0202a9d0(100) ? 1 : 0;
}

void SetupStageParams_020bdf10(StageParams *params, int stage, int level)
{
    int count = 0;
    int found;
    int base;
    int i;
    StageEntry *entry;

    SeedSharedRandomState_0202a984(data_0206085c.seed, data_0206085c.seed, 0);
    found = 0;
    base = 0;
    if (stage != 0) {
        do {
            if (data_ov034_020bf970[base].kind == -1) {
                found++;
            }
            base++;
        } while (found != stage);
    }
    while (data_ov034_020bf970[base + count].kind != -1) {
        count++;
    }
    entry = &data_ov034_020bf970[base + level - 1];
    if (stage == 0x1a) {
        params->stageId = data_0206085c.stageId;
        params->level = data_0206085c.level;
        params->floorCount = data_0206085c.floorCount;
        if (data_0206085c.level % 10 == 0) {
            params->layout = entry->layout;
            params->mapId = entry->mapId;
            for (i = 0; i < 3; i++) {
                params->values[i] = entry->values[i];
            }
            params->bonusRolled = RollStageBonus(entry);
        } else {
            params->layout = data_ov034_020be9d8[data_0206085c.layoutIndex].layout;
            params->mapId = data_ov034_020be9d8[data_0206085c.layoutIndex].mapId;
            for (i = 0; i < 3; i++) {
                params->values[i] = data_0206085c.level;
            }
            params->bonusRolled = data_0206085c.hasBonus;
        }
    } else {
        if (level == 1) {
            params->stageId = data_ov034_020bf970[base + count].values[0];
        }
        params->level = level;
        params->floorCount = count;
        params->layout = entry->layout;
        params->mapId = entry->mapId;
        for (i = 0; i < 3; i++) {
            params->values[i] = entry->values[i];
        }
        params->bonusRolled = RollStageBonus(entry);
    }
    if (stage == 0x1a && data_0206085c.level % 10 != 0) {
        CopyStageEntry(params, &data_ov034_020bf970[base + 0x14 + data_0206085c.variant]);
        if (params->layout == 0xf) {
            params->backdrop = 0x1e;
        }
    } else {
        CopyStageEntry(params, entry);
    }
    if (params->bonusRolled) {
        params->bonusC = 1;
    }
    params->active = 1;
    params->retries = 0;
    params->timer = 0;
    params->progress = 0;
    params->cleared = 0;
    params->timeLimit = entry->timeLimit;
    for (i = 0; i < 3; i++) {
        params->colors[i] = data_ov034_020bea58[entry->kind][i];
    }
    for (i = 0; i < 4; i++) {
        params->rewardItems[i] = data_ov034_020beb0c[entry->rewardSet].pairs[i].item;
        params->rewardCounts[i] = data_ov034_020beb0c[entry->rewardSet].pairs[i].count;
    }
}
