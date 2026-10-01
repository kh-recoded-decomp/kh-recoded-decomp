#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern int func_ov046_020c14fc(void);
extern int func_ov042_020bd4ac(void);
extern int func_ov043_020bcacc(void);

int QuerySubModeStatus_020af3f4(void)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        return func_ov046_020c14fc();
    case 1:
        return func_ov042_020bd4ac();
    case 2:
        return func_ov043_020bcacc();
    case 3:
        return 0;
    }
    return 0;
}
