#include "nitro/types.h"

extern int func_0200234c(u16 value);

BOOL IsResultZero_02009028(u16 *value) {
    if (func_0200234c(*value) == 0) {
        return 1;
    }
    return 0;
}
