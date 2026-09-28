#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x50];
    u32 value;
} InnerRecord;

typedef struct {
    u8 pad_00[8];
    InnerRecord *inner;
} OuterRecord;

/* Reads a value through a nested pointer. */
u32 func_ov008_020a0d80(OuterRecord *self)
{
    return self->inner->value;
}
