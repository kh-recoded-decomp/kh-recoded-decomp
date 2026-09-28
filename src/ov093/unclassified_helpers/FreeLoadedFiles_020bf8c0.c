#include "nitro/types.h"

typedef struct {
    void *loadedFiles[3];
} SceneWork;

extern void ZeroHalfThenFree_0202cd78(void *file);

void FreeLoadedFiles_020bf8c0(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree_0202cd78(work->loadedFiles[i]);
    }
}
