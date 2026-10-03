#include "nitro/types.h"

extern int *data_ov021_020b56a0;

extern void func_ov046_020c1724(void *arg);

void ForwardSubModeEnd_020af7e4(void *arg) {
    switch (*data_ov021_020b56a0) {
    case 0:
        func_ov046_020c1724(arg);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
