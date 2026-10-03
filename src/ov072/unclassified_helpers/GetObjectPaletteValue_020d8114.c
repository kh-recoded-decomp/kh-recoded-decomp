#include "nitro/types.h"

extern const u32 data_ov072_020d9bdc[2][4];
extern BOOL func_ov072_020d8100(void *object);
extern int GetClampedPaletteSlot_02073598(void);

u32 GetObjectPaletteValue_020d8114(void *object)
{
    BOOL isType = func_ov072_020d8100(object) != 0;

    return data_ov072_020d9bdc[isType][GetClampedPaletteSlot_02073598()];
}
