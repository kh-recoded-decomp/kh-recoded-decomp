#include "nitro/types.h"

typedef struct Owner
{
    u8 pad_00[0x6C];
    int state;
} Owner;

typedef struct Handle
{
    Owner *owner;
    int kind;
} Handle;

BOOL func_ov001_020847c4(Handle *handle)
{
    if (handle->kind == 4)
    {
        int state = handle->owner->state;
        if (state == 1 || state == 0x15 || (u32)(state - 0x17) <= 2)
            return FALSE;
    }
    return TRUE;
}
