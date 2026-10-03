#include "nitro/types.h"

typedef struct RecordSet {
    u8 pad_00[0xc];
    u32 low : 30;
    u32 hasExtra : 1;
    u32 high : 1;
} RecordSet;

typedef struct RecordC {
    u8 pad_00[6];
    s16 recordIds[0x14];
} RecordC;

extern s32 data_ov002_0206aebc[];
extern void func_ov002_020687a4(RecordSet *set, s32 *recordIds, int count);
extern void ClearPackedField_02069308(RecordSet *set, int fieldIndex, int matchIndex);
extern BOOL IsRecordSlotAcquired_02051ea8(s32 slot);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern RecordC *GetRecordTableCEntry_0205225c(s32 index);

BOOL ApplyCategoryRecord_02069190(RecordSet *set, int category, int offset)
{
    s32 recordId;
    int slot = category;
    s16 *ids;
    BOOL acquired;
    int i;

    if (category >= 0x14) {
        slot = 0x10;
    }
    recordId = data_ov002_0206aebc[slot];
    if (recordId != -1) {
        if (offset < 0) {
            return TRUE;
        }
        recordId = recordId + offset;
        func_ov002_020687a4(set, &recordId, 1);
        if (set->hasExtra && ((category >= 1 && category < 6) || category == 0x11)) {
            recordId = 0;
            func_ov002_020687a4(set, &recordId, 1);
        }
        return TRUE;
    }
    for (i = 3; i < 0x16; i++) {
        ClearPackedField_02069308(set, i, -1);
    }
    acquired = IsRecordSlotAcquired_02051ea8(10);
    if (!acquired) {
        AcquireRecordSlot_02051d3c(10, 1);
    }
    if (set->hasExtra) {
        ApplyCategoryRecord_02069190(set, 0, 0);
    }
    ids = GetRecordTableCEntry_0205225c(offset)->recordIds;
    for (i = 3; i < 0x14; i++) {
        if (i != 0x12 && (recordId = ids[i]) != -1) {
            func_ov002_020687a4(set, &recordId, 1);
        }
    }
    if (!acquired) {
        ReleaseRecordSlot_02051dfc(10);
    }
    return TRUE;
}
