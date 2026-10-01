#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern void Camera_SetFrozen_020c0bec(BOOL frozen);
extern void func_ov043_020bcb14(BOOL frozen);
extern void func_ov044_020d0120(BOOL frozen);

void SetSubModeFrozen_020af434(BOOL frozen)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        Camera_SetFrozen_020c0bec(frozen);
        break;
    case 1:
        break;
    case 2:
        func_ov043_020bcb14(frozen);
        break;
    case 3:
        func_ov044_020d0120(frozen);
        break;
    }
}
