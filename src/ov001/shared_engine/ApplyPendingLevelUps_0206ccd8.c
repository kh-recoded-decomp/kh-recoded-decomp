#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28cc];
    u32 experience;
    u8 pad_28D0[0x6];
    u8 level;
} SaveData;

typedef struct EventEntry {
    u32 unk_00;
    void *object;
    u8 pad_08[0x20];
} EventEntry;

typedef struct EventContext {
    u32 unk_00;
    EventEntry entries[3];
} EventContext;

extern SaveData *g_saveData_0205fe0c;
extern EventContext *g_eventContext_020a049c;
extern u32 GetLevelExperience_020500fc(u8 level);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern u16 AddRecordItem_02029240(int index, const void *src);

int ApplyPendingLevelUps_0206ccd8(void)
{
    SaveData *save = g_saveData_0205fe0c;
    int level = save->level;
    int step;
    int levelsGained;
    int newLevel;
    int i;

    if (g_eventContext_020a049c->entries[0].object == NULL) {
        return 0;
    }
    if (level >= 50) {
        return 0;
    }
    if (save->experience < GetLevelExperience_020500fc(level)) {
        return 0;
    }
    for (step = 1, levelsGained = 1; step < 50 - level; step++, levelsGained++) {
        save = g_saveData_0205fe0c;
        if (save->experience < GetLevelExperience_020500fc(level + step)) {
            break;
        }
    }
    newLevel = level + levelsGained;
    if (newLevel > 50) {
        newLevel = 50;
    } else if (newLevel < 0) {
        newLevel = 0;
    }
    save->level = newLevel;
    if (!IsGlobalPackedBitSet_02027304(0x90)) {
        SetGlobalPackedBit_02027320(0x90);
    }
    for (i = 0; i < levelsGained; i++) {
        AddRecordItem_02029240(0x90, NULL);
    }
    return levelsGained;
}
