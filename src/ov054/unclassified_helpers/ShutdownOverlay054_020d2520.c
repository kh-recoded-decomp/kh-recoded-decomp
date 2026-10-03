#include "nitro/types.h"

typedef struct OverlayActor {
    u8 pad_0000[0x126c];
    int savedMode;
} OverlayActor;

typedef struct FieldState {
    u8 pad_0000[0x27b5];
    u8 savedMode;
} FieldState;

extern OverlayActor *data_ov054_020d3700;
extern FieldState *data_ov001_020a0460;
extern void DestroyActorResources_020ccc60(OverlayActor *actor);
extern void func_ov058_020d7ee8(void);

void ShutdownOverlay054_020d2520(void)
{
    OverlayActor *actor = data_ov054_020d3700;
    int mode;

    if (actor != NULL) {
        mode = actor->savedMode;
        data_ov001_020a0460->savedMode = mode;
        DestroyActorResources_020ccc60(actor);
        func_ov058_020d7ee8();
        data_ov054_020d3700 = NULL;
    }
}
