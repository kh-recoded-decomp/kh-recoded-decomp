#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
    void *loadedFiles[3];
} SceneWork;

extern const char *data_ov099_020c2288[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

void LoadMessageFiles_020bf3f0(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        work->loadedFiles[i] = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov099_020c2288[i], 0xe, FALSE);
    }
}
