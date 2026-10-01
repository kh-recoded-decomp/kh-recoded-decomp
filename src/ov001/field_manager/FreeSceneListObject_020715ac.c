#include "nitro/types.h"

typedef struct Scene {
    u8 pad_000[0x5d0];
    u8 objectList[0xc];
} Scene;

typedef struct SceneGlobals {
    int allocEnabled;
    Scene *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04a4;
extern void RemoveIntrusiveListObject_020129d8(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeSceneListObject_020715ac(void *object)
{
    SceneGlobals *globals = &data_ov001_020a04a4;

    globals->allocEnabled = 0;
    RemoveIntrusiveListObject_020129d8(globals->scene->objectList, object);
    globals->allocEnabled = 1;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(object);
}
