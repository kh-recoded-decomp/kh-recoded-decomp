#define data_0206039c gSceneHeapReference
#include "eu/src/HeapRecord.h"

/* The shared scene view stores this record as an array of words. */
static inline void ResetSceneHeapRecord(void *storage)
{
    ResetHeapRecord((HeapRecord *)storage);
}

#define AdvancePendingScene_02025570 AdvancePendingScene
#define data_02055da0 gSceneTable
#define data_0205fdec gSceneController
#define data_0205fdec_alias gSceneControllerStorage
#define func_020253f8 ResetCallbackTable
#define func_02029f78 LoadOverlayAfterGeometryTransfer
#define func_02029f98 UnloadOverlayAfterGeometryTransfer
#define func_0202a0f0 ResetSceneHeapRecord
#define func_0202a448 CreateTaskObject
#define func_0202a5a4 StoreWord0
#define func_0202a720 CollectFinishedTask
#include "src/arm9/scene_dispatch/AdvancePendingScene_02025570.c"
