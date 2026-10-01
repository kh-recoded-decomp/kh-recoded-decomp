#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x4];
    s32 isValid;
    u8 pad_08[0x4];
    s32 category;
    u8 pad_10[0x8];
} RecordB;

typedef struct RecordFlagSets {
    u8 primaryBits[0x67];
    u8 secondaryBits[0x67];
} RecordFlagSets;

extern u16 data_ov002_0206adb4[];
extern s32 data_ov002_0206aebc[];
extern BOOL IsRecordSlotAcquired_02051ea8(s32 slot);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void ReleaseRecordSlot_02051dfc(s32 slot);
extern RecordB *GetRecordTableBEntry_02052238(s32 index);

s32 GetRecordFlagState_02069aac(RecordFlagSets *flagSets, s32 recordId, BOOL checkPrimary) {
    s32 byteIndex;
    u8 mask;
    RecordB *record;
    s32 categoryIndex;
    s32 bitIndex;
    BOOL wasAcquired;
    u8 secondary;

    wasAcquired = IsRecordSlotAcquired_02051ea8(9);
    if (!wasAcquired) {
        AcquireRecordSlot_02051d3c(9, 1);
    }
    record = GetRecordTableBEntry_02052238(recordId);
    if (record->isValid == 0) {
        return -1;
    }
    categoryIndex = record->category - 1;
    bitIndex = data_ov002_0206adb4[categoryIndex] + (recordId - data_ov002_0206aebc[categoryIndex]);
    byteIndex = bitIndex >> 3;
    mask = 1 << (u8)(bitIndex - (byteIndex << 3));
    if (!wasAcquired) {
        ReleaseRecordSlot_02051dfc(9);
    }
    secondary = flagSets->secondaryBits[byteIndex];
    if (!checkPrimary) {
        return (mask & secondary) != 0;
    }
    if (mask & secondary) {
        return (mask & flagSets->primaryBits[byteIndex]) ? 1 : -1;
    }
    return 0;
}
