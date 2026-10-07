#include "src/overlays/ov028/Ov028FieldState.h"

u32 GetFieldTransitionFlags(void)
{
    return gOv028FieldState->flags & 0x60;
}
