#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedList {
    void *head;
    void *tail;
} LinkedList;

typedef struct Selection {
    u8 pad_00[4];
    s32 index;
    s32 unk_08;
} Selection;

typedef struct SceneWork {
    u32 unk_00;
    LinkedList list;
    u8 pad_0c[0x20];
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[4];
    Selection selection;
    fx32 unk_48;
    fx32 unk_4C;
    u8 unk_50[0x7c];
    u8 unk_CC[1];
} SceneWork;

extern SceneWork *data_ov001_020a0484;
extern u8 data_ov001_0209eb2c[];
extern SceneWork *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov001_0206b930(LinkedList *list);
extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void func_0202c690(int arg0);
extern void *func_0202c940(void *info, void *textureHeader, int flag);
extern int func_0202d3c8(void *objectBase, int recordIndex);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);
extern void func_ov001_0206c19c(void *target, void *objectBase);
extern void func_ov001_0206be78(void *target, void *objectBase);
extern void func_ov001_0206c704(void *callback);
extern void func_ov001_0206c46c(void);
extern void func_ov001_0206ae84(void);

void *InitSceneWork_0206adc8(void)
{
    SceneWork *work = NNSi_FndGetCurrentRootHeap_0202a764();
    Selection *selection;
    void *slot;
    void *objectBase;

    data_ov001_020a0484 = work;
    work->unk_00 = 0xcc;
    work->unk_2C = 0;
    work->unk_30 = 0;
    work->unk_34 = 0;
    func_ov001_0206b930(&work->list);
    selection = &work->selection;
    selection->unk_08 = 0;
    selection->index = -1;
    work->unk_48 = 0x14000;
    work->unk_4C = 0xa000;
    slot = RetainOrInitializeSharedRecord_0202c80c((int)data_ov001_0209eb2c, 0x11);
    func_0202c690(0);
    objectBase = func_0202c940(slot, NULL, 1);
    func_0202c690(1);
    func_0202d3c8(objectBase, 7);
    func_ov001_0206c19c(work->unk_50, objectBase);
    func_ov001_0206be78(work->unk_CC, objectBase);
    ReleaseSharedRecordSlot_0202c8a8(slot);
    func_ov001_0206c704(func_ov001_0206c46c);
    return func_ov001_0206ae84;
}
