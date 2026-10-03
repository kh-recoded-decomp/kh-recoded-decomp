#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c0d88(int first, int second);
extern void func_ov042_020bd0fc(int first, int second);
extern void func_ov043_020bc8e0(int first, int second);

void ForwardSubModePairB_020af57c(int first, int second)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c0d88(first, second);
        break;
    case 1:
        func_ov042_020bd0fc(first, second);
        break;
    case 2:
        func_ov043_020bc8e0(first, second);
        break;
    case 3:
        break;
    }
}
