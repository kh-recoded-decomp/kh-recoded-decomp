#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    s32 count;
} RecordB;

typedef struct {
    u8 pad_00[0xc];
    u8 *data;
} MainDataHolder_0205fe00;

extern RecordB *GetRecordTableBEntry_02052238(s32 index);
extern MainDataHolder_0205fe00 g_mainDataHolder_0205fe00;
extern u16 data_0205347c[];
extern s32 data_0205351c[];

int func_020277f4(s32 param1, s32 *outByteIndex, u8 *outMask)
{
    RecordB *entry = GetRecordTableBEntry_02052238(param1);
    s32 idx = entry->count - 1;
    s32 bitIndex = data_0205347c[idx] + (param1 - data_0205351c[idx]);
    s32 byteIndex = bitIndex >> 3;
    u8 bitPos = (u8)(bitIndex - byteIndex * 8);
    u8 mask = (u8)(1 << bitPos);
    if (outByteIndex != 0) {
        *outByteIndex = byteIndex;
    }
    if (outMask != 0) {
        *outMask = mask;
    }
    if ((g_mainDataHolder_0205fe00.data[byteIndex + 0x2788] & mask) != 0) {
        return 1;
    }
    return 0;
}
