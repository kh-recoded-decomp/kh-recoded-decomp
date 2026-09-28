#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x77];
    u8 status;
} ObjectState;

u8 func_ov016_020a6af4(ObjectState *obj)
{
    return obj->status;
}
