#include "nitro/types.h"

extern BOOL func_ov001_02063838(void);
extern BOOL func_ov001_02088858(void);
extern int func_ov001_02063a38(void);
extern BOOL func_ov036_020bc668(void);

BOOL func_02028518(void) {
    if (func_ov001_02063838() != 0 && func_ov001_02088858() != 0) {
        return 1;
    }
    if (func_ov001_02063a38() == 8 && func_ov036_020bc668() != 0) {
        return 1;
    }
    return 0;
}
