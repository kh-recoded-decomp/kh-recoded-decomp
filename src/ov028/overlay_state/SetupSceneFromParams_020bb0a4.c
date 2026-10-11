#include "nitro/types.h"

typedef struct {
    s8 mode;
    s8 kind;
    s16 x;
    s16 y;
} SceneParams;

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    s8 mode;
    u8 pad_09[0x17];
    int state;
} SceneState;

extern SceneState *data_ov028_020bb380;
extern u8 data_020608c8;

extern BOOL func_ov001_020645c8(u32 value);
extern void SetupFlaggedSelectionRecords_0204f778(void);
extern void FlushPendingFieldUpdate_020633d4(void);
extern BOOL QueueFieldUpdate_020633a0(int request);

static inline void ApplySceneParams(const SceneParams *params) {
    data_ov028_020bb380->x = params->x;
    data_ov028_020bb380->y = params->y;
    data_ov028_020bb380->kind = params->kind;
    data_ov028_020bb380->flags = 3;
    data_ov028_020bb380->flags |= 0x20;
    data_ov028_020bb380->mode = params->mode;
    data_ov028_020bb380->state = 0;
}

void SetupSceneFromParams_020bb0a4(const SceneParams *params) {
    u8 before;

    ApplySceneParams(params);
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x3609 + 1)) {
        before = data_020608c8;
        SetupFlaggedSelectionRecords_0204f778();
        if (before != data_020608c8) {
            FlushPendingFieldUpdate_020633d4();
            QueueFieldUpdate_020633a0(0);
        }
    }
}




