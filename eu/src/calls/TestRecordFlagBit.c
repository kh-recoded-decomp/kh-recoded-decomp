#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    s32 count;
} RecordB;

typedef struct {
    u8 pad_00[0xc];
    u8 *data;
} MainDataHolder;

extern RecordB *GetRecordTableBEntry(s32 index);
extern MainDataHolder data_0205fe00;
extern u16 data_02053490[];
extern s32 data_02053530[];

int TestRecordFlagBit(s32 recordId, s32 *outByteIndex, u8 *outMask)
{
    RecordB *record = GetRecordTableBEntry(recordId);
    s32 category = record->count - 1;
    s32 bitIndex = data_02053490[category] + (recordId - data_02053530[category]);
    s32 byteIndex = bitIndex >> 3;
    u8 bitPosition = (u8)(bitIndex - byteIndex * 8);
    u8 mask = (u8)(1 << bitPosition);

    if (outByteIndex != NULL) {
        *outByteIndex = byteIndex;
    }
    if (outMask != NULL) {
        *outMask = mask;
    }

    return (data_0205fe00.data + byteIndex)[0x2788] & mask ? 1 : 0;
}
