#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TaggedKey {
    u32 kind;
    union {
        s32 value;
        struct {
            s16 first;
            s16 second;
        } pair;
    } key;
} TaggedKey;

typedef struct CameraTargetSelection {
    TaggedKey target;
    u8 reserved08[12];
} CameraTargetSelection;

/* Only the target-selection prefix of the shared field context is used here. */
typedef struct CameraTargetStateView {
    u32 reserved00;
    CameraTargetSelection selected;
} CameraTargetStateView;

typedef char TaggedKeySizeCheck[sizeof(TaggedKey) == 8 ? 1 : -1];
typedef char TargetSelectionSizeCheck[sizeof(CameraTargetSelection) == 0x14 ? 1 : -1];
typedef char TargetSelectionOffsetCheck[
    (u32)&((CameraTargetStateView *)0)->selected == 4 ? 1 : -1];
typedef char TargetPositionSizeCheck[sizeof(VecFx32) == 12 ? 1 : -1];

enum {
    TARGET_PAD_R = 0x100,
    TARGET_PAD_L = 0x200,
    TARGET_PAD_RIGHT = 0x10,
    TARGET_PAD_LEFT = 0x20
};

extern u16 data_020604fc;
extern u16 data_02060500;
extern void *data_ov001_020a04a4;
extern BOOL ResolveCameraTargetPosition(VecFx32 *position);
extern BOOL FindSideTarget(s32 direction, const VecFx32 *position, fx32 *limit);
extern BOOL MatchesTaggedKey(TaggedKey *expected, TaggedKey *actual);

BOOL HandleSideTargetButtons(void)
{
    CameraTargetStateView *context;
    BOOL changed;
    s32 direction;
    u16 held;
    u16 pressed;
    VecFx32 position;
    CameraTargetSelection previous;

    held = data_020604fc;
    changed = FALSE;
    direction = 0;
    pressed = data_02060500;

    /* Both shoulders enable cycling; Right takes priority over Left. */
    if ((held & TARGET_PAD_R) && (held & TARGET_PAD_L)) {
        if (pressed & TARGET_PAD_RIGHT) {
            direction = TARGET_PAD_R;
        } else if (pressed & TARGET_PAD_LEFT) {
            direction = TARGET_PAD_L;
        }
    }
    if (direction == 0) {
        return FALSE;
    }
    /* Resolving a path target can itself advance the selected target. */
    if (ResolveCameraTargetPosition(&position)) {
        return TRUE;
    }

    context = data_ov001_020a04a4;
    previous = context->selected;
    if (FindSideTarget(direction, &position, NULL)) {
        if (!MatchesTaggedKey(&context->selected.target, &previous.target)) {
            changed = TRUE;
        }
    }
    return changed;
}
