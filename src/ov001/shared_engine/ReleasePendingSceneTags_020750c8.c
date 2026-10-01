#include "nitro/types.h"

typedef struct SceneTagState {
    u8 pad[0x44];
    int tagCount;
    u8 pad48[8];
    u32 releasePending : 1;
    u32 unk50 : 31;
} SceneTagState;

extern SceneTagState *data_ov001_020a04ac;
extern void *GetSceneTagTracker_020711b0(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void func_ov027_020b7f60(void *pool, void *record, int flag);

void ReleasePendingSceneTags_020750c8(void) {
    SceneTagState *state = data_ov001_020a04ac;
    int i;
    void *tracker = GetSceneTagTracker_020711b0();
    int pairs;

    if (state->releasePending) {
        state->releasePending = 0;
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x14));
        pairs = (state->tagCount + 1) / 2;
        for (i = 0; i < pairs; i++) {
            func_ov027_020b7f60(tracker, FindActiveRecordById_020b8184(tracker, (u16)(i + 50000)), 1);
        }
        state->tagCount = 0;
    }
}
