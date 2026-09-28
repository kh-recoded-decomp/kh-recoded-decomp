#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xAC];
    s16 shortValue;
    u8 byteValue;
} UnkObj_020a1b08;

void func_ov007_020a1b08(UnkObj_020a1b08 *obj, s32 *outShort, u32 *outByte)
{
    *outShort = obj->shortValue;
    *outByte = obj->byteValue;
}
