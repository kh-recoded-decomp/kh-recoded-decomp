#include "nitro/types.h"

extern u16 *func_02004a00(void);

u16 GetU16Field_020049f0(void) {
    u16 *field;

    field = func_02004a00();
    return *field;
}
