#include "nitro/types.h"

typedef int (*SceneStepFn)(void);

typedef struct SceneSystemClassDescriptor {
    u16 classId;
    u16 subId;
    SceneStepFn (*initialize)(void);
    void (*shutdown)(void);
    u32 workSize;
    void *heapReference;
} SceneSystemClassDescriptor;

extern SceneStepFn InitSceneSystem(void);
extern void PanelState_NoOpE(void);
extern u8 data_02060394[];

/* Obj_Construct copies the IDs, allocates work, and calls initialize. */
SceneSystemClassDescriptor gSceneSystemClassDescriptor = {
    0, 17,
    InitSceneSystem,
    PanelState_NoOpE,
    8,
    data_02060394
};
