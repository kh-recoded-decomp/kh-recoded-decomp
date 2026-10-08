#include "nitro/types.h"

typedef struct {
    const char *names[3];
} MsgContainerNames;

typedef struct {
    s32 loaded;
    void *containers[3];
} MsgContainerSet;

extern const MsgContainerNames gEffectResourceSets;
extern s32 data_ov021_020b5640;
extern u8 data_ov021_020b5644;
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

#define gMsgContainers (*(MsgContainerSet *)((u8 *)&data_ov021_020b5644 - 4))

void LoadMsgContainers(void)
{
    MsgContainerNames list = gEffectResourceSets;
    int i;

    for (i = 0; i < 3; i++) {
        gMsgContainers.containers[i] = Msg_OpenContainerAndReadHeader(list.names[i], 0x11, FALSE);
    }
    data_ov021_020b5640 = TRUE;
}
