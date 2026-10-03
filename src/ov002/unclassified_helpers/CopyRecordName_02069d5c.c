#include "nitro/types.h"

typedef struct RecordC {
    u8 pad_00[0x30];
    const u16 *name;
} RecordC;

extern s32 data_ov002_0206aebc[];
extern void CopyRecordTableBField_02069d04(s32 index, u16 *dst);
extern BOOL IsRecordSlotAcquired_02051ea8(s32 slot);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern RecordC *GetRecordTableCEntry_0205225c(s32 index);
extern u16 *CopyWideStringBounded_020663d0(u16 *dst, const u16 *src, int maxLength);

void CopyRecordName_02069d5c(s32 category, s32 index, u16 *dst)
{
    BOOL wasAcquired;
    s32 base = data_ov002_0206aebc[category];

    if (base != -1) {
        CopyRecordTableBField_02069d04(base + index, dst);
        return;
    }
    wasAcquired = IsRecordSlotAcquired_02051ea8(10);
    if (!wasAcquired) {
        AcquireRecordSlot_02051d3c(10, 1);
    }
    CopyWideStringBounded_020663d0(dst, GetRecordTableCEntry_0205225c(index)->name, 0x3f);
    if (!wasAcquired) {
        ReleaseRecordSlot_02051dfc(10);
    }
}
