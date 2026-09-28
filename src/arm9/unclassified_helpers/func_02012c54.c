#include "nitro/types.h"

typedef struct {
    u16 type;
    u16 pad;
    u32 size;
    u32 zero1;
    u32 zero2;
} Header;

typedef struct {
    Header *buffer;
    u32 end;
} Range;

Header *func_02012c54(Range *range, u16 type)
{
    Header *header = range->buffer;
    u32 end = range->end;

    header->type = type;
    header->pad = 0;
    header->size = end - ((u32)header + 16);
    header->zero1 = 0;
    header->zero2 = 0;
    return header;
}
