#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *messages[3];
} Ov101State;

extern const char *gReportTopResourcePaths[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadReportTopMessageContainers(Ov101State *state)
{
    int i;

    for (i = 0; i < 3; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader(gReportTopResourcePaths[i], 0xE, FALSE);
    }
}
