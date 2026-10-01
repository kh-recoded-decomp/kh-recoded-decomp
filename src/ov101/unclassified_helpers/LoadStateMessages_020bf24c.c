#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1C];
    void *messages[5];
} Ov101State;

extern const char *data_ov101_020c0dcc[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void LoadStateMessages_020bf24c(Ov101State *state)
{
    int i;

    for (i = 0; i < 5; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov101_020c0dcc[i], 0xE, FALSE);
    }
}
