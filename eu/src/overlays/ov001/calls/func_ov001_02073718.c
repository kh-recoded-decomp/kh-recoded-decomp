#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x1c];
    u8 recordPool[0x476 - 0x1c];
    u16 iconBlendValue;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback(void *pool, void *record);
extern void BlendIconTiles(u32 value);

void func_ov001_02073718(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    TagTracker_InvokeCallback(manager->recordPool, FindActiveRecordById(manager->recordPool, 10));
    TagTracker_InvokeCallback(manager->recordPool, FindActiveRecordById(manager->recordPool, 11));
    BlendIconTiles(manager->iconBlendValue);
}
