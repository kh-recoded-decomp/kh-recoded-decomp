#include "nitro/types.h"

typedef struct {
    u32 ids[3];
} AnimIdTable;

typedef struct {
    u8 pad_000[0x1c];
    u8 animPool[0x1fc - 0x1c];
    int animState;
} Scene;

typedef struct {
    u32 unk0;
    Scene *scene;
} SceneHolder;

extern SceneHolder data_ov001_020a04a4;
extern const AnimIdTable data_ov001_0209dbdc;
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);

void SetSceneAnimState_02072fc4(int state)
{
    Scene *scene = data_ov001_020a04a4.scene;
    AnimIdTable table = data_ov001_0209dbdc;
    void *pool = scene->animPool;

    if (state != scene->animState) {
        scene->animState = state;
        if (state <= -1) {
            InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, table.ids[0]));
            return;
        }
        TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, table.ids[state]));
    }
}
