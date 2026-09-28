#include "nitro/types.h"

extern int data_020608c8;

void SetParamHalf18_02050630(u16 value)
{
    *(u16 *)((char *)&data_020608c8 + 0x12) = value;
}
