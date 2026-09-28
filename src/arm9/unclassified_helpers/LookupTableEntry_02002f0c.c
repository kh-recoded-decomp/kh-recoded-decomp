#include "nitro/types.h"

extern u16 GetU16Field_020049f0(void);
extern void *data_020526d8[];

void *LookupTableEntry_02002f0c(void)
{
    return data_020526d8[GetU16Field_020049f0()];
}
