#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void func_ov046_020c16c0(void);
extern void func_ov039_020bd084(void);
extern void func_ov044_020d0b88(void);

void NotifySubModeEvent_020af6c4(void)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        func_ov046_020c16c0();
        break;
    case 1:
        break;
    case 2:
        func_ov039_020bd084();
        break;
    case 3:
        func_ov044_020d0b88();
        break;
    }
}
