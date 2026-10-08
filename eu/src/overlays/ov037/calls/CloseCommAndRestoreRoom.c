#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
    u8 keepAudio : 1;
    u8 pad_0a[0x12];
    s32 result;
} CommState;

typedef struct FieldState {
    u8 pad_000[0x24a];
    s16 roomId;
} FieldState;

extern CommState *gContinueSceneState;
extern FieldState *data_ov001_020a0480;
extern void DestroyOv037Context(void);
extern void PopVramState(void);
extern int func_ov001_020644b0(void);
extern void SetFieldStateValue(int roomId, int mode);
extern void Set_SessionFlagBit0(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern void StoreToGlobalPtr4Field28(int value);

s32 CloseCommAndRestoreRoom(void)
{
    CommState *state = gContinueSceneState;

    if (state->keepAudio) {
        state->result = 0;
    } else {
        DestroyOv037Context();
    }
    gContinueSceneState->flags &= ~0xc;
    PopVramState();
    if (state->result == 0) {
        if (func_ov001_020644b0() == 900) {
            SetFieldStateValue(-4, 1);
        } else {
            SetFieldStateValue(data_ov001_020a0480->roomId, 1);
        }
        Set_SessionFlagBit0();
    }
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    gContinueSceneState->flags |= 0x8000;
    return 10;
}
