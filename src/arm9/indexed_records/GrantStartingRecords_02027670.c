#include "nitro/types.h"

typedef struct OwnerInfo {
    u8 language;
    u8 favoriteColor;
    u8 birthMonth;
    u8 birthDay;
    u16 nickName[11];
    u16 nickNameLength;
    u16 comment[27];
    u16 commentLength;
} OwnerInfo;

typedef struct RecordB {
    u8 pad_00[8];
    s32 tag;
} RecordB;

typedef struct RecordC {
    u8 pad_00[6];
    s16 recordIndices[20];
} RecordC;

extern u32 data_020534a4[];

/* Unsigned divide helper returns the remainder in r1. */
extern u64 DivModU32_02023fc8(u32 dividend, u32 divisor);

extern void func_02004ac8(void *dest);
extern void CopySharedSettings_02004ae4(OwnerInfo *info);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern RecordC *GetRecordTableCEntry_0205225c(s32 index);
extern RecordB *GetRecordTableBEntry_02052238(s32 index);
extern s32 func_0202761c(u32 handle);
extern BOOL EquipRecordList_02027858(s32 *recordIndices, s32 count);
extern u32 func_0202a9d0(u32 range);
extern s32 PickRandomRecordInCategory_02027e18(s32 category, s32 requiredTag);

void GrantStartingRecords_02027670(void)
{
    s32 recordIndex;
    u8 macAddress[6];
    OwnerInfo owner;
    s32 tag = -1;
    u32 seed = 0;
    u16 setIndex;
    s16 *setRecords;
    s32 i;

    func_02004ac8(macAddress);
    CopySharedSettings_02004ae4(&owner);
    for (i = 0; i < 6; i++) {
        seed += macAddress[i];
    }
    for (i = 0; i < owner.nickNameLength; i++) {
        seed += owner.nickName[i];
    }
    setIndex = (u32)(DivModU32_02023fc8(seed, 91) >> 32);
    if (setIndex >= 8) {
        setIndex++;
    }
    if (setIndex >= 0x35) {
        setIndex++;
    }
    AcquireRecordSlot_02051d3c(9, 1);
    AcquireRecordSlot_02051d3c(10, 1);
    setRecords = GetRecordTableCEntry_0205225c(setIndex)->recordIndices;
    for (i = 0; i < 20; i++) {
        if (i == 18) {
            continue;
        }
        recordIndex = setRecords[i];
        if (recordIndex == -1) {
            continue;
        }
        func_0202761c(recordIndex);
        if (tag == -1 && i >= 6) {
            RecordB *record = GetRecordTableBEntry_02052238(recordIndex);
            if (record->tag != -1) {
                tag = record->tag;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        recordIndex = i;
        func_0202761c(recordIndex);
        if (i == 0) {
            EquipRecordList_02027858(&recordIndex, 1);
        }
    }
    for (i = 0; i < 5; i++) {
        recordIndex = i + 0x10;
        func_0202761c(recordIndex);
        if (i == 0) {
            EquipRecordList_02027858(&recordIndex, 1);
        }
    }
    for (i = 0; i < 0x21; i++) {
        recordIndex = i + 0x20;
        func_0202761c(recordIndex);
        if (i == 0) {
            EquipRecordList_02027858(&recordIndex, 1);
        }
    }
    for (i = 0; i < 11; i++) {
        recordIndex = data_020534a4[i];
        func_0202761c(recordIndex);
        if (i == 0) {
            EquipRecordList_02027858(&recordIndex, 1);
        }
    }
    for (i = 3; i < 20; i++) {
        recordIndex = PickRandomRecordInCategory_02027e18(i + 1, func_0202a9d0(100) < 70 ? tag : -1);
        if (recordIndex != -1) {
            func_0202761c(recordIndex);
        }
    }
    for (i = 0; i < 20; i++) {
        if (i == 18) {
            continue;
        }
        recordIndex = setRecords[i];
        if (recordIndex == -1) {
            continue;
        }
        EquipRecordList_02027858(&recordIndex, 1);
    }
    ReleaseRecordSlot_02051dfc(10);
    ReleaseRecordSlot_02051dfc(9);
}
