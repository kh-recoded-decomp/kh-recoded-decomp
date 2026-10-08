#include "nitro/types.h"

extern void EndOverlay41Phase(void);
extern int UpdateStageFrame(void);

u32 func_ov035_020ba6c0(void) {
    if (UpdateStageFrame() != 0) {
        EndOverlay41Phase();
        return 7;
    }
    return 0xffffffff;
}
