#include "nitro/types.h"

typedef struct SceneParams {
    s8 mode;
    s8 sceneId;
    s16 argA;
    s16 argB;
} SceneParams;

typedef struct SceneWork {
    s16 sceneId;
    s16 argA;
    s16 argB;
    s16 state;
    u8 unknown_08[8];
    void *task;
    int handle;
    int counter;
    s8 mode;
    u8 unknown_1d[5];
    s16 colorA;
    s16 colorB;
    u8 unknown_26[0x0a];
    s16 selection;
    u8 unknown_32[0x0a];
    int cursor;
} SceneWork;

extern SceneWork *data_ov035_020bc4e0;
extern SceneWork *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void LoadSlotEntriesFromBits_02050120(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void func_ov035_020ba898(void);
extern void LoadPzTextureParams_02066488(void);
extern void CreateSessionTask_0206c6dc(void);
extern void *CreateOverlayTask_0206a6f4(int id);
extern void func_ov035_020ba458(void);

void *InitMovieSceneWork_020ba3e0(SceneParams *params) {
    data_ov035_020bc4e0 = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov035_020bc4e0->sceneId = params->sceneId;
    data_ov035_020bc4e0->argA = params->argA;
    data_ov035_020bc4e0->argB = params->argB;
    data_ov035_020bc4e0->selection = -1;
    data_ov035_020bc4e0->cursor = -1;
    data_ov035_020bc4e0->handle = -1;
    data_ov035_020bc4e0->colorB = 0xff;
    data_ov035_020bc4e0->colorA = 0xff;
    data_ov035_020bc4e0->state = 0x23;
    LoadSlotEntriesFromBits_02050120();
    CreateSessionNameMenu_02063ba4();
    func_ov035_020ba898();
    LoadPzTextureParams_02066488();
    CreateSessionTask_0206c6dc();
    data_ov035_020bc4e0->task = CreateOverlayTask_0206a6f4(data_ov035_020bc4e0->sceneId);
    data_ov035_020bc4e0->mode = params->mode;
    data_ov035_020bc4e0->counter = 0;
    return func_ov035_020ba458;
}
