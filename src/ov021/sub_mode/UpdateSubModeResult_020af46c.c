#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern int func_ov046_020c1540(void);
extern int func_ov040_020bd0d4(void);
extern int func_ov036_020bc8b4(void);
extern int func_ov044_020d00f0(void);

int UpdateSubModeResult_020af46c(void)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        return func_ov046_020c1540();
    case 1:
        return func_ov040_020bd0d4();
    case 2:
        return func_ov036_020bc8b4();
    case 3:
        return func_ov044_020d00f0();
    }
    return 0;
}
