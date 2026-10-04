#include "nitro/types.h"

typedef struct SceneWork SceneWork;

typedef void (*SceneStateHandler)(SceneWork *work);

struct SceneWork {
    u8 pad_0000[0xd1d8];
    int blinkTimer;
    int blinkPhase;
};

extern const SceneStateHandler data_ov093_020c3c7c[];
extern int func_ov093_020c2348(SceneWork *work);
extern void func_ov093_020bfd60(int index, SceneWork *work);
extern void UpdateScrollBarDrag_020c1d48(SceneWork *work);
extern void ResetObjManagerLists_020c02f0(SceneWork *work);

void UpdateSceneFrame_020bedb0(SceneWork *work)
{
    SceneStateHandler handler = data_ov093_020c3c7c[func_ov093_020c2348(work)];

    if (handler != NULL) {
        handler(work);
    }
    if (++work->blinkTimer >= 60) {
        work->blinkTimer = 0;
        work->blinkPhase = (work->blinkPhase + 1) % 2;
        func_ov093_020bfd60(0, work);
    }
    if (func_ov093_020c2348(work) == 6) {
        UpdateScrollBarDrag_020c1d48(work);
    }
    ResetObjManagerLists_020c02f0(work);
}
