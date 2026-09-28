#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *handle;
    u32 flags;
    u8 pad_10[8];
    u8 field_18[4];
} CommandState;

extern void *func_02004938(void);
extern void func_0200494c(void *token);
extern void func_02002aa8(void *queue);
extern int func_0200a2fc(CommandState *state, u32 type);
extern void func_0200a200(u32 *node, u32 value);
extern CommandState *func_0200a67c(void *handle, int flag);
extern void func_0200a828(CommandState *state);

void AdvanceCommandQueue_0200a8ac(CommandState *state) {
    void *token = func_02004938();
    while ((state->flags & 0x40) == 0 && (state->flags & 1) != 0) {
        func_02002aa8(state->field_18);
    }
    func_0200494c(token);
    if ((state->flags & 0x40) == 0) {
        return;
    }
    {
        void *handle;
        int result;
        handle = state->handle;
        result = func_0200a2fc(state, (*(volatile u32 *)&state->flags >> 8) & 0xff);
        func_0200a200((u32 *)state, (u32)result);
        state = func_0200a67c(handle, 1);
    }
    if (state == 0) {
        return;
    }
    func_0200a828(state);
}
