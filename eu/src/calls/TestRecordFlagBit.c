#include "nitro/types.h"
#include "src/data/RecordCategoryTables.h"

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

int TestRecordFlagBit(s32 recordId, s32 *outByteIndex, u8 *outMask)
{
    RecordB *record = GetRecordTableBEntry(recordId);
    s32 category = record->count - 1;
    s32 bitIndex = gRecordCategoryFlagBitOffsets[category] + (recordId - gRecordCategoryFirstIds[category]);
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
