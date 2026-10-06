#include "nitro/types.h"

typedef struct FieldValueState {
    u8 pad_00[2];
    s16 defaultValue;
    u8 pad_04[2];
    s16 currentValue;
    u8 pad_08[4];
    u32 lowFlags : 6;
    u32 wasNegative : 1;
    u32 midFlags : 2;
    u32 locked : 1;
    u32 highFlags : 22;
} FieldValueState;

typedef struct FieldState {
    u8 pad_0000[0x208];
    FieldValueState value;
    u8 pad_0218[0x268c];
    u8 mode;
} FieldState;

extern FieldState *data_ov001_020a0480;
extern void SetGlobalStateValue(u32 value);

void SetFieldStateValue(int value, u8 mode)
{
    FieldState *field = data_ov001_020a0480;
    FieldValueState *state = &field->value;

    if (!state->locked && value != 0) {
        if (value == -1) {
            state->currentValue = state->defaultValue;
        } else if (value < 0) {
            state->wasNegative = TRUE;
            state->currentValue = value;
        } else {
            state->currentValue = value;
        }
        SetGlobalStateValue(-1);
    }
    field->mode = mode;
}

