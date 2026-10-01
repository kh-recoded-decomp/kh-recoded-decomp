#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern int func_ov046_020c15e8(void);
extern int func_ov040_020bd0f0(void);
extern int func_ov036_020bc8bc(void);
extern int func_ov044_020d0110(void);

int func_ov021_020af5f4(void)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        return func_ov046_020c15e8();
    case 1:
        return func_ov040_020bd0f0();
    case 2:
        return func_ov036_020bc8bc();
    case 3:
        return func_ov044_020d0110();
    }
    return 0;
}
