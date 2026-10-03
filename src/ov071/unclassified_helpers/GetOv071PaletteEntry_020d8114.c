#include "nitro/types.h"

extern int data_ov071_020d967c[2][4];
extern BOOL func_ov071_020d8100(void *obj);
extern int GetClampedPaletteSlot_02073598(void);

int GetOv071PaletteEntry_020d8114(void *obj)
{
    int row = func_ov071_020d8100(obj) != 0;

    return data_ov071_020d967c[row][GetClampedPaletteSlot_02073598()];
}
