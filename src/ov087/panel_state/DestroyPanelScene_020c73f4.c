#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ObjectList;

typedef struct {
    u32 id;
    u8 model[0x104];
} ListEntry;

typedef struct {
    u8 pad_000[0x8];
    int entryCount;
    u8 pad_00C[0x8];
    u8 headerModel[0x104];
    ListEntry entries[8];
    u8 pad_958[0x38];
    ObjectList cursorList;
    ObjectList frameList;
    ObjectList slotLists[3];
    ObjectList tabLists[2];
    ObjectList labelList;
    ObjectList iconList;
    void *workBuffer;
} PanelScene;

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void *func_ov039_020bc18c(void);
extern void func_ov027_020b7f8c(void *ctx, int arg);
extern void *func_ov039_020bc1bc(void);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void func_ov027_020b903c(void *container);
extern void func_ov027_020b9098(void *container, u32 value);
extern void FreePointerIfSet_020ba294(void **ptr);
extern BOOL DestroyFndObjectList_020014f0(ObjectList *list);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_ov087_020c64d8(void);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);

void DestroyPanelScene_020c73f4(PanelScene *scene)
{
    int index;

    ReleaseResourceAndDetach_0202eee8(scene->headerModel);
    for (index = 0; index < scene->entryCount; index++) {
        ReleaseResourceAndDetach_0202eee8(scene->entries[index].model);
    }
    func_ov027_020b7f8c(func_ov039_020bc18c(), 0);
    DestroyAllContainerElements_020b900c(func_ov039_020bc1bc());
    func_ov027_020b903c(func_ov039_020bc1bc());
    func_ov027_020b9098(func_ov039_020bc1bc(), 0);
    FreePointerIfSet_020ba294(&scene->workBuffer);
    DestroyFndObjectList_020014f0(&scene->iconList);
    DestroyFndObjectList_020014f0(&scene->labelList);
    DestroyFndObjectList_020014f0(&scene->frameList);
    DestroyFndObjectList_020014f0(&scene->cursorList);
    for (index = 0; index < 3; index++) {
        DestroyFndObjectList_020014f0(&scene->slotLists[index]);
    }
    for (index = 0; index < 2; index++) {
        DestroyFndObjectList_020014f0(&scene->tabLists[index]);
    }
    ReleaseRecordSlot_02051dfc(2);
    func_ov087_020c64d8();
    SetSecondaryElementEnabled_020bc084(TRUE);
}
