#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_0000[0x27b6];
    u8 lowBits : 6;
    u8 pendingSubModels : 1;
    u8 highBit : 1;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern BOOL func_ov001_020645c8(u32 value);
extern void SetSubModelsEnabled_020ceaf4(void *entity, int enable);
extern void SetEntityModeEnabled_020ce7a0(void *entity, int mode, int enable);

void SetEntityModeHideSubModels_020d28e4(void *entity, int mode, int enable)
{
    if (mode == 2) {
        BOOL allowed = TRUE;
        if (func_ov001_020645c8(0x351f) || data_ov001_020a0460->pendingSubModels) {
            allowed = FALSE;
        }
        if (enable && allowed) {
            SetSubModelsEnabled_020ceaf4(entity, 0);
        }
        if (enable && data_ov001_020a0460->pendingSubModels) {
            data_ov001_020a0460->pendingSubModels = 0;
        }
    }
    SetEntityModeEnabled_020ce7a0(entity, mode, enable);
}
