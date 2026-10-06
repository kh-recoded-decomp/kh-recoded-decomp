#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern int func_ov046_020c1608(void);
extern int func_ov042_020bd110(void);
extern int func_ov043_020bc8dc(void);
extern int func_ov044_020d0130(void);

int func_ov021_020af614(void)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        return func_ov046_020c1608();
    case 1:
        return func_ov042_020bd110();
    case 2:
        return func_ov043_020bc8dc();
    case 3:
        return func_ov044_020d0130();
    }
    return 0;
}
