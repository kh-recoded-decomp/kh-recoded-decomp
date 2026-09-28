#include "nitro/types.h"

extern u32 func_02025dac(void);
extern void func_ov003_02064980(u32 stream);
extern void func_ov003_02065028(u32 stream, u32 tick);
extern void func_ov003_0206507c(u32 stream);

/* Resets, then catches up, a movie subtitle stream. */
u32 ResyncMovieSubtitleStream_02064818(int context)
{
    u32 tick;

    tick = func_02025dac();
    func_ov003_02064980(**(u32 **)(context + 0x1c8));
    func_ov003_02065028(**(u32 **)(context + 0x1c8), tick);
    func_ov003_0206507c(**(u32 **)(context + 0x1c8));
    return 1;
}
