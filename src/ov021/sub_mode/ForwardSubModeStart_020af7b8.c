#include "nitro/types.h"

extern int *data_ov021_020b56a0;

extern void func_ov046_020c16f8(void);

void ForwardSubModeStart_020af7b8(void) {
    switch (*data_ov021_020b56a0) {
    case 0:
        func_ov046_020c16f8();
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
