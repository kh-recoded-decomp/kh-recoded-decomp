#include "nitro/types.h"

typedef struct {
    u8 pad_00[16];
    void *messages[2];
} Ov101State;

extern const char *data_ov101_020c04a0[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void func_ov103_020beef4(Ov101State *state)
{
    int i;

    for (i = 0; i < 2; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov101_020c04a0[i], 0xE, FALSE);
    }
}
