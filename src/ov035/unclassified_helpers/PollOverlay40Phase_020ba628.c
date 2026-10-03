#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern int func_ov040_020bd918(void);
extern void EndOverlay40Phase_020bace8(void);

int PollOverlay40Phase_020ba628(void)
{
    int result = func_ov040_020bd918();

    if (result != 0) {
        EndOverlay40Phase_020bace8();
        if (result == 1) {
            g_movieContext_020bc4e0->flags |= 0x8000;
            return 5;
        }
        g_movieContext_020bc4e0->flags |= 0x8000;
        return 8;
    }
    return -1;
}