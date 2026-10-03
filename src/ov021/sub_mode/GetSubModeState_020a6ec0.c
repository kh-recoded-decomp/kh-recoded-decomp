#include "nitro/types.h"

typedef struct SubModeOwner {
    u8 pad_00[6];
    u8 state;
    u8 pad_07[0xd];
    u8 busy;
} SubModeOwner;

extern int UpdateSubModeResult_020af46c(void);

u8 GetSubModeState_020a6ec0(SubModeOwner *owner, BOOL update)
{
    u8 state = owner->state;
    if (update && owner->busy == 0 && UpdateSubModeResult_020af46c()) {
        state = 0;
    }
    return state;
}
