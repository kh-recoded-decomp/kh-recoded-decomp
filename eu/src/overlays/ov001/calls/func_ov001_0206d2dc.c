#include "nitro/types.h"

typedef struct EventStatus {
    u8 pad_00[0xc];
    s32 pending;
} EventStatus;

typedef struct EventContext {
    u8 pad_00[0x8];
    s32 param;
    u8 pad_0C[0x1c];
    u16 flags;
    u8 pad_2A[0xb2];
    EventStatus status;
} EventContext;

extern EventContext *data_ov001_020a04bc;
extern void RefreshFieldMenuPage(s32 param);

void func_ov001_0206d2dc(void)
{
    EventContext *context = data_ov001_020a04bc;
    EventStatus *status = &context->status;

    if ((context->flags & 8) && !(context->flags & 0x10) && status->pending == 0) {
        RefreshFieldMenuPage(context->param);
    }
}
