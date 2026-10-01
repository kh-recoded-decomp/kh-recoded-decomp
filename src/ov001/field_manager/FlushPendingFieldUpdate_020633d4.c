#include "nitro/types.h"

typedef struct FieldFlags {
    u8 pad_00[0x76];
    u8 lowFlags : 3;
    u8 updatePending : 1;
    u8 highFlags : 4;
} FieldFlags;

typedef struct FieldState {
    u8 pad_0000[0x2740];
    FieldFlags flags;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern void func_ov001_0206d84c(void);

void FlushPendingFieldUpdate_020633d4(void)
{
    FieldState *field = data_ov001_020a0460;
    FieldFlags *flags = &field->flags;

    if (flags->updatePending) {
        func_ov001_0206d84c();
        flags->updatePending = FALSE;
    }
}
