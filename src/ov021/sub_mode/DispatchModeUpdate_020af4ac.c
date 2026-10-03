#include "nitro/types.h"

typedef struct ModeParams {
    int a;
    int b;
    int c;
    int d;
} ModeParams;

extern void func_ov046_020c0b34(int arg);
extern ModeParams *func_ov042_020bd590(void);
extern void func_ov042_020bd020(int arg, int c, int d, int a, int b);
extern void func_ov043_020bc820(int arg);
extern void func_ov044_020d0080(int arg);

extern int *data_ov021_020b56a0;

void DispatchModeUpdate_020af4ac(int arg)
{
    ModeParams *params;

    switch (*data_ov021_020b56a0) {
    case 0:
        func_ov046_020c0b34(arg);
        break;
    case 1:
        params = func_ov042_020bd590();
        func_ov042_020bd020(arg, params->c, params->d, params->a, params->b);
        break;
    case 2:
        func_ov043_020bc820(arg);
        break;
    case 3:
        func_ov044_020d0080(arg);
        break;
    }
}
