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

extern FieldSceneHandle data_ov001_020a04a4;
extern const char data_ov001_0209edb8[];
extern char OverlayId27_0000001b[];

extern void func_ov001_0206fbec(FieldScene *scene);
extern void NotifyBothOrOne_02001154(u32 a, const char *b, int index);
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *object);
extern void FreeSceneListObject_020715ac(void *object);
extern void func_ov001_0206f2f8(FieldScene *scene);
extern void func_ov001_0206f848(FieldScene *scene);
extern void func_ov001_0206f720(FieldScene *scene);
extern void func_ov001_0206f6cc(FieldScene *scene);
extern void func_ov001_0206f648(FieldScene *scene);
extern void func_ov001_0206f464(FieldScene *scene);
extern void func_ov001_0206f1dc(FieldScene *scene);
extern void func_ov001_0206f174(FieldScene *scene);
extern int ZeroHalfThenFree_0202cd78(void *archive);
extern void func_02029f98(int processor, int overlayId);
extern void *PXI_Init_02028950(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void SetParamHalf18_02050630(u16 value);
extern void SetParamWord20_02050640(int value);

void ShutdownFieldScene_02070d94(void)
{
    void *object;
    void *next;
    FieldScene *scene = data_ov001_020a04a4.scene;

    func_ov001_0206fbec(scene);
    NotifyBothOrOne_02001154(1, data_ov001_0209edb8, 0);
    object = NNS_FndGetNextListObject_02012a38(scene->objectList, NULL);
    while (object != NULL) {
        next = NNS_FndGetNextListObject_02012a38(scene->objectList, object);
        FreeSceneListObject_020715ac(object);
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
    ZeroHalfThenFree_0202cd78(scene->archives[2]);
    ZeroHalfThenFree_0202cd78(scene->archives[1]);
    ZeroHalfThenFree_0202cd78(scene->archives[0]);
    func_02029f98(0, (int)OverlayId27_0000001b);
    PXI_Init_02028950();
    ZeroHalfThenFree_0202cd78(scene->archives[3]);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->screenBuffers[0]);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->screenBuffers[2]);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->screenBuffers[1]);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->screenBuffers[3]);
    if (scene->extraBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->extraBuffer);
    }
    SetParamHalf18_02050630(scene->savedParam);
    SetParamWord20_02050640(scene->savedFlag == 1);
    data_ov001_020a04a4.scene = NULL;
}
