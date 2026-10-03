#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c1694(int value);
extern void func_ov044_020d0b84(int value);

void ForwardSubModeValue_020af694(int value)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c1694(value);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        func_ov044_020d0b84(value);
        break;
    }
}
