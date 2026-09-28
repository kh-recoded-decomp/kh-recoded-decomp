#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *handle;
    u32 flags;
    u8 pad_10[8];
    u8 field_18[4];
} SoundState;

extern void *func_02004938(void);
extern void func_0200494c(void *token);
extern void func_02002af8(void *buffer);
extern int func_0200a2fc(SoundState *state, u32 type);
extern SoundState *func_0200a67c(void *handle, int flag);

void func_0200a828(SoundState *state) {
    void *handle = state->handle;
    if (state == 0) {
        return;
    }
    do {
        void *token = func_02004938();
        state->flags = state->flags | 0x40;
        if (state->flags & 4) {
            func_02002af8(state->field_18);
            state = 0;
        }
        func_0200494c(token);
        if (state == 0) {
            return;
        }
        {
            int result = func_0200a2fc(state, (state->flags >> 8) & 0xff);
            if (result == 0x100) {
                return;
            }
        }
        state = func_0200a67c(handle, 1);
    } while (state != 0);
}
