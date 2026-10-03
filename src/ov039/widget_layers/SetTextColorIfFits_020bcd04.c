#include "nitro/types.h"

extern int data_ov039_020bea00;
extern void Obj_SetField14_02001490(int *object, int value);
extern int func_02001908(int *object, int text, int flags);

BOOL SetTextColorIfFits_020bcd04(int *object, int limit, int text)
{
    int base = data_ov039_020bea00;
    BOOL fits;

    Obj_SetField14_02001490(object, base + 0xca90);
    fits = func_02001908(object, text, 0) < limit;
    if (!fits) {
        Obj_SetField14_02001490(object, base + 0xcaa8);
    }
    return fits;
}
