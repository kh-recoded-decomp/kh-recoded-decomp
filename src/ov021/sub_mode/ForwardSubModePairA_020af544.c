#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c1578(int first, int second);
extern void func_ov043_020bc8cc(int first, int second);
extern void func_ov044_020d0560(int first, int second);

void ForwardSubModePairA_020af544(int first, int second)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c1578(first, second);
        break;
    case 1:
        break;
    case 2:
        func_ov043_020bc8cc(first, second);
        break;
    case 3:
        func_ov044_020d0560(first, second);
        break;
    }
}
