#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 entryCount;
    u8 pad_0CC[0x6C];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00 : 9;
    u32 altControls : 1;
    u32 unk_10 : 6;
    u32 swapActions : 1;
} ControlConfig;

typedef struct {
    u8 pad_0000[0x2878];
    ControlConfig controls;
} SaveData;

typedef struct {
    u32 recordIds[2][2][3];
} ButtonRecordTable;

extern const ButtonRecordTable data_ov001_0209dee4;
extern SaveData *g_saveData_0205fe0c;

extern void *GetSceneTagTracker_020711b0(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void TriggerFieldMenuButtonRecords_020771a8(FieldMenu *menu)
{
    ButtonRecordTable table = data_ov001_0209dee4;
    void *pool = GetSceneTagTracker_020711b0();
    u32 *recordIds;

    if (menu->unk_138 == 0) {
        return;
    }
    recordIds = table.recordIds[g_saveData_0205fe0c->controls.altControls][g_saveData_0205fe0c->controls.swapActions];
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, recordIds[2]));
    if (menu->entryCount < 2) {
        return;
    }
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, recordIds[0]));
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, recordIds[1]));
}
