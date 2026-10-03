#include "nitro/types.h"

typedef struct BufferSet {
    BOOL allocated;
    void *buffers[3];
} BufferSet;

extern BOOL g_buffersAllocated_020b5620;
extern BufferSet g_bufferSet_020b5620;
extern int ZeroHalfThenFree_0202cd78(void *buffer);

void FreeSharedBuffers_020a9568(void)
{
    int i;

    if (g_buffersAllocated_020b5620) {
        for (i = 0; i < 3; i++) {
            ZeroHalfThenFree_0202cd78(g_bufferSet_020b5620.buffers[i]);
        }
    }
    g_buffersAllocated_020b5620 = FALSE;
}
