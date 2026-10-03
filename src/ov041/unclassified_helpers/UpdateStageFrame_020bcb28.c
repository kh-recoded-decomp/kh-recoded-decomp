#include "nitro/types.h"

typedef struct {
    u8 pad_000[1];
    u8 kind;
    u8 pad_002[0xda];
    u16 entryId;
    u8 pad_0de[0x3d6];
} StageEntry;

typedef struct {
    s32 frameCount;
    u8 pad_04[2];
    u8 phase;
    u8 pad_07[0xd];
    StageEntry *entries;
    u8 pad_18;
    u8 entryCount;
} StageWork;

extern u8 *data_ov035_020bc4e0;
extern void (*data_ov041_020cf8c0[])(void);
extern void func_ov041_020be078(void);
extern void UpdateSceneFade_020bcce8(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern void UpdateChannelLevel_020bc250(u8 kind, u16 id);
extern void func_ov001_02074fa8(u8 kind, u16 id, int mode);
extern void RefreshActiveMenuEntry_02074f7c(u8 kind, u16 id, int mode);

int UpdateStageFrame_020bcb28(void) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    int i;

    data_ov041_020cf8c0[work->phase]();
    if (work->phase >= 5 && work->phase <= 0x13) {
        work->frameCount++;
    }
    func_ov041_020be078();
    UpdateSceneFade_020bcce8();
    for (i = 0; i < work->entryCount; i++) {
        StageEntry *entry = &work->entries[i];
        u8 kind;
        u16 id;
        id = entry->entryId;
        kind = entry->kind;
        if (IsHudFlag9Set_02072884()) {
            UpdateChannelLevel_020bc250(kind, id);
            func_ov001_02074fa8(kind, id, 7);
        } else {
            RefreshActiveMenuEntry_02074f7c(kind, id, 7);
        }
    }
    if (work->phase == 0x16) {
        return 0x8000;
    }
    return 0;
}
