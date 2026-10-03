#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c15f4(void *arg);
extern void func_ov044_020d0ad0(void *arg);

void CopySubModeState_020af634(void *arg)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c15f4(arg);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        func_ov044_020d0ad0(arg);
        break;
    }
}
