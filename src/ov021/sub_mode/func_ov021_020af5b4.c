#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;

extern int func_ov046_020c15a4(void);
extern int func_ov040_020bd290(void);
extern int func_ov036_020bca1c(void);
extern int func_ov044_020d0564(void);

int func_ov021_020af5b4(void)
{
    switch (data_ov021_020b56a0->mode) {
    case 0:
        return func_ov046_020c15a4();
    case 1:
        return func_ov040_020bd290();
    case 2:
        return func_ov036_020bca1c();
    case 3:
        return func_ov044_020d0564();
    }
    return 0;
}
