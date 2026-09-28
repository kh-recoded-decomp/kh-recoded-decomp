#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    u32 pending;
    u8 pad_20[0x34 - 0x20];
    u32 ready;
    u8 pad_38[0x19bc - 0x38];
    u8 embedded[1];
} Ov045EmbeddedState;

extern Ov045EmbeddedState *g_ov045Context_020c0880;

extern void func_0200153c(void *object);

/* Registers a pending embedded object and marks it ready. */
void RegisterEmbeddedObjectIfPending_020c0720(void)
{
    if (g_ov045Context_020c0880->pending != 0) {
        func_0200153c(g_ov045Context_020c0880->embedded);
        g_ov045Context_020c0880->ready = 1;
    }
}
