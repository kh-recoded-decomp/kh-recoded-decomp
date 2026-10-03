#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
    u8 keepAudio : 1;
} CommState;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 lowFlags : 13;
    u32 selectionLocked : 1;
    u8 pad_218[0x3c];
    u8 selection;
    u8 pad_255[0x25a7];
    s8 pendingSlot;
} FieldState;

extern CommState *g_commState_020bb760;
extern FieldState *data_ov001_020a0460;
extern BOOL func_ov001_020645c8(int bitId);
extern u8 func_ov037_020ba544(void);
extern void RefreshSessionSelections_02064c44(void);

s32 SyncSessionCommFlags_020ba764(void)
{
    g_commState_020bb760->keepAudio = (u8)func_ov001_020645c8(0x3525);
    if (!data_ov001_020a0460->selectionLocked) {
        data_ov001_020a0460->selection = func_ov037_020ba544();
        RefreshSessionSelections_02064c44();
        data_ov001_020a0460->pendingSlot = -1;
    }
    g_commState_020bb760->flags |= 0x8000;
    return 2;
}
