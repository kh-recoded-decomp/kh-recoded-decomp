#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c1668(int first, int second, int third);
extern void func_ov044_020d0b24(int first, int second, int third);

void ForwardSubModeEvent_020af664(int first, int second, int third)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c1668(first, second, third);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        func_ov044_020d0b24(first, second, third);
        break;
    }
}
