#include "nitro/types.h"

typedef struct StageEventRecord {
    u8 pad_000[6];
    u16 lowFlags : 9;
    u16 usesSlotTable : 1;
    u16 highFlags : 6;
    u8 pad_008[6];
    u16 type;
    u8 pad_010[0x1a7];
    u8 slotGroup : 2;
    u8 slotIndex : 6;
} StageEventRecord;

extern int data_ov001_0209f2c8;
extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern int func_ov016_020a6dd8(u32 group, u32 index, int arg);
extern int func_ov001_020958f4(StageEventRecord *record, int arg);

int DispatchStageEventArg_020878d4(u32 id, int arg)
{
    StageEventRecord *record;

    if (data_ov001_0209f2c8 != -1 && id != 0) {
        record = GetStageEventRecord_0209c0ec(id);
        if (record != NULL) {
            if (record->type == 99 && record->usesSlotTable) {
                return func_ov016_020a6dd8(record->slotGroup, record->slotIndex, arg);
            }
            return func_ov001_020958f4(record, arg);
        }
    }
    return 0;
}
