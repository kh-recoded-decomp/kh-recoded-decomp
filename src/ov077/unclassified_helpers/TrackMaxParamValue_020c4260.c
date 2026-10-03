#include "nitro/types.h"

typedef struct {
    u8 pad[0xa];
    u16 value;
} ParamBlock;

extern ParamBlock *func_020505a8(void);
extern void SetParamHalf18_02050630(u16 value);

void TrackMaxParamValue_020c4260(u8 *work)
{
    ParamBlock *params = func_020505a8();
    u16 value = params->value;
    if (value > *(u16 *)(work + 0x14d0c)) {
        *(u16 *)(work + 0x14d0c) = value;
    }
    SetParamHalf18_02050630(*(u16 *)(work + 0x14d0c));
}
