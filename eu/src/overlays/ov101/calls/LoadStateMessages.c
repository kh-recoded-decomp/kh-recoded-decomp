#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *messages[5];
} Ov101State;

extern const char *data_ov101_020c19d0[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadStateMessages(Ov101State *state)
{
    int i;

    for (i = 0; i < 5; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader(
            data_ov101_020c19d0[i], 0xE, FALSE
        );
    }
}
