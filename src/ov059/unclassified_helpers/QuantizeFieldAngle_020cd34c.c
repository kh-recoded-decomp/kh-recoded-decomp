#include "nitro/types.h"

extern u16 GetFieldAt0x2_020a7550(void *obj);
extern u16 AddQuantizedViewAngle_020cd2c4(u16 angle);

u16 QuantizeFieldAngle_020cd34c(void *obj)
{
    return AddQuantizedViewAngle_020cd2c4(GetFieldAt0x2_020a7550(obj) + 0x3fff);
}
