#include "nitro/types.h"

typedef struct {
    const char *names[3];
} MsgContainerNames;

typedef struct {
    s32 loaded;
    void *containers[3];
} MsgContainerSet;

extern const MsgContainerNames data_ov021_020b51fc;
extern MsgContainerSet g_msgContainers_020b5620;
extern s32 g_msgContainersLoaded_020b5620;
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void LoadMsgContainers_020a9524(void)
{
    MsgContainerNames list = data_ov021_020b51fc;
    int i;

    for (i = 0; i < 3; i++) {
        g_msgContainers_020b5620.containers[i] = Msg_OpenContainerAndReadHeader_0202cc6c(list.names[i], 0x11, FALSE);
    }
    g_msgContainersLoaded_020b5620 = 1;
}
