#include "nitro/types.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_R 0x0100

extern BOOL func_ov021_020a752c(void *inputState, u16 buttonMask);

BOOL IsButtonAOrRActive_020cba14(void *inputState)
{
    if (func_ov021_020a752c(inputState, PAD_BUTTON_A) ||
        func_ov021_020a752c(inputState, PAD_BUTTON_R)) {
        return TRUE;
    }
    return FALSE;
}
