#include "nitro/types.h"

typedef struct {
    BOOL allocated;
    void *buffers[3];
} SharedBufferSet;

extern BOOL data_ov021_020b5640;
extern u8 data_ov021_020b5644;
extern int ZeroHalfThenFree(void *buffer);

#define gSharedBuffers (*(SharedBufferSet *)((u8 *)&data_ov021_020b5644 - 4))

void FreeSharedBuffers(void)
{
    int i;

    if (data_ov021_020b5640) {
        for (i = 0; i < 3; i++) {
            ZeroHalfThenFree(gSharedBuffers.buffers[i]);
        }
    }
    data_ov021_020b5640 = FALSE;
}
