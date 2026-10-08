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

extern FieldSceneHandle data_ov001_020a04c4;
extern const char sOv001_BTLUITASK_0209edd8[];
extern char OVERLAY_27_ID[];

extern void func_ov001_0206fbec(FieldScene *scene);
extern void NotifyBothOrOne(u32 a, const char *b, int index);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void FreeSceneListObject(void *object);
extern void func_ov001_0206f2f8(FieldScene *scene);
extern void func_ov001_0206f848(FieldScene *scene);
extern void func_ov001_0206f720(FieldScene *scene);
extern void func_ov001_0206f6cc(FieldScene *scene);
extern void func_ov001_0206f648(FieldScene *scene);
extern void func_ov001_0206f464(FieldScene *scene);
extern void func_ov001_0206f1dc(FieldScene *scene);
extern void func_ov001_0206f174(FieldScene *scene);
extern int ZeroHalfThenFree(void *archive);
extern void func_02029fac(int processor, int overlayId);
extern void *PXI_Init_02028964(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void SetParamHalf18(u16 value);
extern void SetParamWord20(int value);

void ShutdownFieldScene(void)
{
    void *object;
    void *next;
    FieldScene *scene = data_ov001_020a04c4.scene;

    func_ov001_0206fbec(scene);
    NotifyBothOrOne(1, sOv001_BTLUITASK_0209edd8, 0);
    object = NNS_FndGetNextListObject(scene->objectList, NULL);
    while (object != NULL) {
        next = NNS_FndGetNextListObject(scene->objectList, object);
        FreeSceneListObject(object);
        object = next;
    }
    func_ov001_0206f2f8(scene);
    if (scene->activeMenu != NULL) {
        func_ov001_0206f848(scene);
    }
    func_ov001_0206f720(scene);
    func_ov001_0206f6cc(scene);
    func_ov001_0206f648(scene);
    func_ov001_0206f464(scene);
    func_ov001_0206f1dc(scene);
    func_ov001_0206f174(scene);
    ZeroHalfThenFree(scene->archives[2]);
    ZeroHalfThenFree(scene->archives[1]);
    ZeroHalfThenFree(scene->archives[0]);
    func_02029fac(0, (int)OVERLAY_27_ID);
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
    data_ov001_020a04c4.scene = NULL;
}
