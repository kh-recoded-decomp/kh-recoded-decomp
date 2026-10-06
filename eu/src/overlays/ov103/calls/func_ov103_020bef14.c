#include "nitro/types.h"

typedef struct {
    u8 pad_00[16];
    void *messages[2];
} Ov101State;

extern const char *gTheaterReportResourcePaths[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void func_ov103_020bef14(Ov101State *state)
{
    int i;

    for (i = 0; i < 2; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader(gTheaterReportResourcePaths[i], 0xE, FALSE);
    }
}
