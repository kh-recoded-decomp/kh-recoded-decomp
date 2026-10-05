#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldState {
    u8 pad_00[0x62];
    s8 currentArea;
    s8 previousArea;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern VecFx32 *func_ov001_0206dc4c(int slot);
extern s8 FindActorRewardValue(VecFx32 *position);
extern u32 GetBoundedEntryField(int index);
extern void UpdateRewardMenuHighlights(u32 entry, BOOL inArea);

void UpdateAreaFromPosition(void)
{
    FieldState *state;
    BOOL inArea;
    u32 entry;
    VecFx32 position;

    inArea = FALSE;
    state = data_ov035_020bc4e0;
    position = *func_ov001_0206dc4c(0);
    position.y += 0x800;
    state->previousArea = state->currentArea;
    state->currentArea = FindActorRewardValue(&position);
    entry = GetBoundedEntryField(0);
    if (state->currentArea >= 0) {
        inArea = TRUE;
    }
    UpdateRewardMenuHighlights(entry, inArea);
}
