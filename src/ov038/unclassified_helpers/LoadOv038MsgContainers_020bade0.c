#include "nitro/types.h"

typedef struct Ov038Context {
    u32 unk_00;
    void *containers[3];
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern const char *g_ov038ContainerNames_020bbdb0[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void LoadOv038MsgContainers_020bade0(void)
{
    Ov038Context *context = g_ov038Context_020bd144;
    s32 index;

    for (index = 0; index < 3; index++) {
        context->containers[index] = Msg_OpenContainerAndReadHeader_0202cc6c(g_ov038ContainerNames_020bbdb0[index], 0xe, FALSE);
    }
}
