#include "nitro/types.h"

typedef struct OverlayFactoryContext {
    u8 pad_000[0xe8];
    u32 unk_0e8;
} OverlayFactoryContext;

extern OverlayFactoryContext *data_ov001_020a04bc;

u32 func_ov001_0206e644(void)
{
    if (data_ov001_020a04bc == 0) {
        return 0;
    }
    return data_ov001_020a04bc->unk_0e8;
}
