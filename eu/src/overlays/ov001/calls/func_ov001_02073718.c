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
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov001_0206ed8c(u32 value);

void func_ov001_02073718(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    func_ov027_020b8230(manager->recordPool, FindActiveRecordById(manager->recordPool, 10));
    func_ov027_020b8230(manager->recordPool, FindActiveRecordById(manager->recordPool, 11));
    func_ov001_0206ed8c(manager->iconBlendValue);
}
