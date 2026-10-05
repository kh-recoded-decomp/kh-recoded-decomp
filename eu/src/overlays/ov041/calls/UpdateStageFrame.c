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
extern void (*data_ov041_020cf8e0[])(void);
extern void func_ov041_020be098(void);
extern void UpdateSceneFade(void);
extern BOOL IsHudFlag9Set(void);
extern void UpdateChannelLevel(u8 kind, u16 id);
extern void func_ov001_02074fa8(u8 kind, u16 id, int mode);
extern void RefreshActiveMenuEntry(u8 kind, u16 id, int mode);

int UpdateStageFrame(void) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    int i;

    data_ov041_020cf8e0[work->phase]();
    if (work->phase >= 5 && work->phase <= 0x13) {
        work->frameCount++;
    }
    func_ov041_020be098();
    UpdateSceneFade();
    for (i = 0; i < work->entryCount; i++) {
        StageEntry *entry = &work->entries[i];
        u8 kind;
        u16 id;
        id = entry->entryId;
        kind = entry->kind;
        if (IsHudFlag9Set()) {
            UpdateChannelLevel(kind, id);
            func_ov001_02074fa8(kind, id, 7);
        } else {
            RefreshActiveMenuEntry(kind, id, 7);
        }
    }
    if (work->phase == 0x16) {
        return 0x8000;
    }
    return 0;
}
