#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *messages[3];
} Ov101State;

extern const char *data_ov101_020c2a24[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void func_ov091_020bf194(Ov101State *state)
{
    int i;

    for (i = 0; i < 3; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov101_020c2a24[i], 0xE, FALSE);
    }
}
