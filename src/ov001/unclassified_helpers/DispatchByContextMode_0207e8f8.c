#include "nitro/types.h"

extern s32 *data_ov001_020a04d4;
extern void _fp_init_0207e2a0(s32 *context);
extern void _fp_init_0207e2a4(s32 *context);

void DispatchByContextMode_0207e8f8(void)
{
    s32 *context = data_ov001_020a04d4;

    switch (*context) {
    case 1:
        _fp_init_0207e2a0(context);
        break;
    case 2:
    case 3:
        _fp_init_0207e2a4(context);
        break;
    }
}
