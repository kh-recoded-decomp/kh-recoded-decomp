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

extern CommState *g_commState_020bb760;
extern FieldState *data_ov001_020a0460;
extern void DestroyOv037Context_020bb448(void);
extern void PopVramState_020365f0(void);
extern int func_ov001_020644b0(void);
extern void func_ov001_02063130(int roomId, int mode);
extern void Set_SessionFlagBit0_020642b4(void);
extern void ReleaseSeqArcHeapLevel_0204e040(int index);
extern void StoreToGlobalPtr4Field28_0202a778(int value);

s32 CloseCommAndRestoreRoom_020ba980(void)
{
    CommState *state = g_commState_020bb760;

    if (state->keepAudio) {
        state->result = 0;
    } else {
        DestroyOv037Context_020bb448();
    }
    g_commState_020bb760->flags &= ~0xc;
    PopVramState_020365f0();
    if (state->result == 0) {
        if (func_ov001_020644b0() == 900) {
            func_ov001_02063130(-4, 1);
        } else {
            func_ov001_02063130(data_ov001_020a0460->roomId, 1);
        }
        Set_SessionFlagBit0_020642b4();
    }
    ReleaseSeqArcHeapLevel_0204e040(1);
    StoreToGlobalPtr4Field28_0202a778(1);
    g_commState_020bb760->flags |= 0x8000;
    return 10;
}
