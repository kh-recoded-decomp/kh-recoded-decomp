#include "nitro/types.h"

typedef struct FieldScene {
    u8 pad_000[0x68];
    void *archives[4];
    u8 pad_078[0x180];
    void *activeMenu;
    u8 pad_1fc[0x264];
    void *screenBuffers[4];
    u8 pad_470[6];
    u16 savedParam;
    u8 pad_478[8];
    u32 lowBits : 16;
    u32 savedFlag : 1;
    u32 highBits : 15;
    u8 pad_484[0x134];
    void *extraBuffer;
    u8 pad_5bc[0x14];
    u8 objectList[0xc];
} FieldScene;

typedef struct FieldSceneHandle {
    u32 unk_00;
    FieldScene *scene;
} FieldSceneHandle;

extern FieldSceneHandle gFieldSceneGlobals;
extern const char sOv001_BTLUITASK_0209edd8[];
extern char OVERLAY_27_ID[];

extern void DestroyFieldHudTasks(FieldScene *scene);
extern void NotifyBothOrOne(u32 a, const char *b, int index);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void FreeSceneListObject(void *object);
extern void ReleaseFieldHudTextResources(FieldScene *scene);
extern void ReleaseFieldChoiceWindow(FieldScene *scene);
extern void ReleaseSceneTextWindow51C(FieldScene *scene);
extern void ReleaseSceneTextWindow4D8(FieldScene *scene);
extern void ReleaseFieldRecordNamesAndEntryList(FieldScene *scene);
extern void ReleaseFieldMessageLineWindow(FieldScene *scene);
extern void ReleaseFieldSceneFonts(FieldScene *scene);
extern void ReleaseFieldHudGraphics(FieldScene *scene);
extern int ZeroHalfThenFree(void *archive);
extern void UnloadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern void *PXI_Init_02028964(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void SetParamHalf18(u16 value);
extern void SetParamWord20(int value);

void ShutdownFieldScene(void)
{
    void *object;
    void *next;
    FieldScene *scene = gFieldSceneGlobals.scene;

    DestroyFieldHudTasks(scene);
    NotifyBothOrOne(1, sOv001_BTLUITASK_0209edd8, 0);
    object = NNS_FndGetNextListObject(scene->objectList, NULL);
    while (object != NULL) {
        next = NNS_FndGetNextListObject(scene->objectList, object);
        FreeSceneListObject(object);
        object = next;
    }
    ReleaseFieldHudTextResources(scene);
    if (scene->activeMenu != NULL) {
        ReleaseFieldChoiceWindow(scene);
    }
    ReleaseSceneTextWindow51C(scene);
    ReleaseSceneTextWindow4D8(scene);
    ReleaseFieldRecordNamesAndEntryList(scene);
    ReleaseFieldMessageLineWindow(scene);
    ReleaseFieldSceneFonts(scene);
    ReleaseFieldHudGraphics(scene);
    ZeroHalfThenFree(scene->archives[2]);
    ZeroHalfThenFree(scene->archives[1]);
    ZeroHalfThenFree(scene->archives[0]);
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
    PXI_Init_02028964();
    ZeroHalfThenFree(scene->archives[3]);
    NNSi_FndFreeFromDefaultHeap(scene->screenBuffers[0]);
    NNSi_FndFreeFromDefaultHeap(scene->screenBuffers[2]);
    NNSi_FndFreeFromDefaultHeap(scene->screenBuffers[1]);
    NNSi_FndFreeFromDefaultHeap(scene->screenBuffers[3]);
    if (scene->extraBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene->extraBuffer);
    }
    SetParamHalf18(scene->savedParam);
    SetParamWord20(scene->savedFlag == 1);
    gFieldSceneGlobals.scene = NULL;
}
