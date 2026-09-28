#include "nitro/types.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 mode;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1c;
} State;

void func_0200b394(State *state) {
    state->field_08 = 0;
    state->field_04 = 0;
    state->field_00 = 0;
    state->field_1c = 0;
    state->field_18 = 0;
    state->mode = state->field_08 | 0x2300;
    state->field_10 = 0;
    state->field_14 = 0;
}
