#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 unk_08;
} RecordB;

extern u8 data_02053468[];
extern s32 data_0205351c[];
extern u32 func_0202a9d0(u32 range);
extern int func_020277f4(s32 recordIndex, s32 *outByteIndex, u8 *outMask);
extern BOOL IsValueInTable_02027ebc(s32 value);
extern RecordB *GetRecordTableBEntry_02052238(s32 index);

s32 PickRandomRecordInCategory_02027e18(s32 category, s32 requiredTag)
{
    s32 recordIndex;
    s32 first;
    s32 end;
    s32 count;
    s32 attempt;
    s32 slot;

    if (category < 1 || category == 0x13) {
        return -1;
    }
    slot = category - 1;
    count = data_02053468[slot];
    first = data_0205351c[slot];
    end = first + count;
    recordIndex = first + func_0202a9d0(count);
    for (attempt = 0; attempt < count; attempt++) {
        if (func_020277f4(recordIndex, NULL, NULL) == 0 && IsValueInTable_02027ebc(recordIndex)) {
            if (requiredTag == -1) {
                break;
            } else {
                RecordB *record = GetRecordTableBEntry_02052238(recordIndex);
                if (record->unk_08 == requiredTag) {
                    break;
                }
            }
        }
        recordIndex++;
        if (recordIndex >= end) {
            recordIndex = first;
        }
    }
    while (!IsValueInTable_02027ebc(recordIndex)) {
        recordIndex++;
        if (recordIndex >= end) {
            recordIndex = first;
        }
    }
    return recordIndex;
}
