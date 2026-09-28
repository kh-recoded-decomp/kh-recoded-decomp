#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *value;
} Context;

extern Context *func_ov017_020a4ee0();

void *func_ov017_020a50d8(void)
{
    Context *context = func_ov017_020a4ee0();
    return context->value;
}
