#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageData {
    u32 flags;
    u8 pad_00004[0x18e4c];
    VecFx32 origin;
} StageData;

extern StageData *data_ov001_020a0508;
extern const VecFx32 data_02053438;

void ResetStageOrigin_0209c3e8(void)
{
    if (data_ov001_020a0508 != NULL) {
        data_ov001_020a0508->flags |= 1;
        data_ov001_020a0508->origin = data_02053438;
    }
}
