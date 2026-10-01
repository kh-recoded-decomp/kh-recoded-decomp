#include "nitro/types.h"

typedef struct MessagePathList {
    const char *paths[9];
} MessagePathList;

typedef struct FieldMessages {
    u8 pad_00[0xb8];
    void *containers[9];
} FieldMessages;

extern FieldMessages *data_ov001_020a049c;
extern const MessagePathList data_ov001_0209ec18;
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void OpenFieldMessageContainers_0206d6d4(void)
{
    FieldMessages *messages = data_ov001_020a049c;
    MessagePathList list = data_ov001_0209ec18;
    int i;

    for (i = 0; i < 9; i++) {
        messages->containers[i] = Msg_OpenContainerAndReadHeader_0202cc6c(list.paths[i], 0x11, FALSE);
    }
}
