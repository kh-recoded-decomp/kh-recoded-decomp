#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *gOv028FieldSceneWorkStorage;

extern BOOL RequestSubsceneMode0Or1FromMode4(void);
extern void StoreToGlobalPtr4Field28(int value);

int SceneState_WaitPanelReady(void) {
    if (!RequestSubsceneMode0Or1FromMode4()) {
        return -1;
    }
    if (gOv028FieldSceneWorkStorage->flags & 1) {
        gOv028FieldSceneWorkStorage->flags &= ~1;
    }
    StoreToGlobalPtr4Field28(0);
    return 7;
}
