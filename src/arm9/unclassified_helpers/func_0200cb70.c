#include "nitro/types.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 context;
    u32 mode;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1c;
    u8 pad_20[0x28];
} DispatchState;

extern void func_0200b394(void *state);
extern s32 func_0200c6fc(void *state, u32 opcode, s32 flag);

void func_0200cb70(void *context)
{
    DispatchState state;
    func_0200b394(&state);
    state.context = (u32)context;
    func_0200c6fc(&state, 9, 0);
}
