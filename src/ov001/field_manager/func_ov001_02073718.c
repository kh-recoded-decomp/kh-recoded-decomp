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

extern FieldManagerHandle data_ov001_020a04a4;

extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void BlendIconTiles_0206ed8c(u32 value);

void func_ov001_02073718(void)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    TagTracker_InvokeCallback_020b8210(manager->recordPool, FindActiveRecordById_020b8184(manager->recordPool, 10));
    TagTracker_InvokeCallback_020b8210(manager->recordPool, FindActiveRecordById_020b8184(manager->recordPool, 11));
    BlendIconTiles_0206ed8c(manager->iconBlendValue);
}
