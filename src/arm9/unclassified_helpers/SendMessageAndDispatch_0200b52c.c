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

extern void func_0200b394(State *state);
extern int func_0200ac28(void *param2, u32 *outWord, void *buffer);
extern int func_0200a930(State *state, u32 type, int wait);

u32 SendMessageAndDispatch_0200b52c(State *state, void *param2, u32 param3) {
    u32 outWord;
    u32 message[3];
    u8 buffer[280];
    u32 result;
    int handle;

    result = 0;
    outWord = 0;
    handle = func_0200ac28(param2, &outWord, buffer);
    if (handle != 0) {
        func_0200b394(state);
        state->field_10 = (u32)message;
        state->field_08 = handle;
        message[0] = outWord;
        message[1] = (u32)buffer;
        message[2] = param3;
        if (func_0200a930(state, 0xd, 1) != 0) {
            result = 1;
        } else {
            state->field_08 = result;
        }
    }
    return result;
}
