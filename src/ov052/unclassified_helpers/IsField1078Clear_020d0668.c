#include "nitro/types.h"

BOOL IsField1078Clear_020d0668(int entity)
{
    BOOL result = TRUE;
    if (*(int *)(entity + 0x1078) != 0) {
        result = FALSE;
    }
    return result;
}
