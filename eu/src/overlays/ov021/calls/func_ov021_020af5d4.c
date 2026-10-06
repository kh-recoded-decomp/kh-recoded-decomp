#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern int Camera_GetActiveController(void);
extern int func_ov042_020bd2b0(void);
extern int func_ov043_020bca3c(void);
extern int func_ov044_020d0584(void);

int func_ov021_020af5d4(void)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        return Camera_GetActiveController();
    case 1:
        return func_ov042_020bd2b0();
    case 2:
        return func_ov043_020bca3c();
    case 3:
        return func_ov044_020d0584();
    }
    return 0;
}
