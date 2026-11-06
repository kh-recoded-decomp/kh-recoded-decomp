#include "nitro/types.h"

typedef struct {
    BOOL allocated;
    void *buffers[3];
} SharedBufferSet;

extern BOOL gEffectResourceContainersLoaded;
extern u8 gEffectResourceContainerStorage;
extern int ZeroHalfThenFree(void *buffer);

#define gSharedBuffers (*(SharedBufferSet *)((u8 *)&gEffectResourceContainerStorage - 4))

void FreeSharedBuffers(void)
{
    int i;

    if (gEffectResourceContainersLoaded) {
        for (i = 0; i < 3; i++) {
            ZeroHalfThenFree(gSharedBuffers.buffers[i]);
        }
    }
    gEffectResourceContainersLoaded = FALSE;
}
