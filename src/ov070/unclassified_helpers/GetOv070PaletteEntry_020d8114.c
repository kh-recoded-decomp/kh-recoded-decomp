#include "nitro/types.h"

extern int data_ov070_020d8a1c[2][4];
extern BOOL func_ov070_020d8100(void *obj);
extern int GetClampedPaletteSlot_02073598(void);

int GetOv070PaletteEntry_020d8114(void *obj)
{
    int row = func_ov070_020d8100(obj) != 0;

    return data_ov070_020d8a1c[row][GetClampedPaletteSlot_02073598()];
}
