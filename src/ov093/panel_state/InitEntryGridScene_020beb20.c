#include "nitro/types.h"

typedef struct {
    u32 vramBase;
    u32 unk_04;
    u32 paletteBase;
    u8 resources[0x200 - 0xc];
    u8 animSets[2][0x6434];
    u8 pad_ca68[0xcf00 - 0xca68];
    int unk_CF00;
    u8 pad_cf04[0xcf4c - 0xcf04];
    int selectedIndex;
    int isClosing;
    u8 pad_cf54[0xd19c - 0xcf54];
    int unk_D19C;
    u8 pad_d1a0[0xd1b8 - 0xd1a0];
    int unk_D1B8;
    int unk_D1BC;
    int unk_D1C0;
    int isLocked;
    int popupHandle;
    int unk_D1CC;
    int unk_D1D0;
    int unk_D1D4;
    int unk_D1D8;
    int unk_D1DC;
    int unk_D1E0;
    u8 pad_d1e4[0xd224 - 0xd1e4];
} SceneWork;

typedef struct {
    u32 vramBase;
    void *resources;
    void *animSet;
    int unk_0C;
} PopupInit;

typedef struct {
    u8 pad_00[8];
    int value;
    u8 pad_0c[0x20];
} PanelDesc;

extern SceneWork *g_sceneWork_020c50e0;
extern PanelDesc data_ov093_020c4038;
extern PanelDesc data_ov093_020c4064;
extern char data_ov093_020c4d34[];

extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dst, u32 size);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetEntryFlag_020c22d4(int flagSet, int entryIndex);
extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void func_ov093_020c0fb0(SceneWork *work);
extern BOOL AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_ov093_020bf67c(SceneWork *work);
extern void func_ov093_020bf880(SceneWork *work);
extern void func_ov093_020bf8e4(SceneWork *work);
extern void func_ov093_020bfac4(SceneWork *work);
extern void func_ov093_020c0100(SceneWork *work);
extern void func_ov093_020c05b8(SceneWork *work);
extern void func_ov093_020c1ca8(SceneWork *work);
extern void func_ov093_020c06ec(PanelDesc *desc, SceneWork *work);
extern void func_ov093_020bfd60(int mode, SceneWork *work);
extern int func_ov093_020c3bdc(PopupInit *init);
extern void func_ov093_020c2b04(void);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel);
extern void func_ov093_020c231c(int state, SceneWork *work);

BOOL InitEntryGridScene_020beb20(SceneWork *work)
{
    PanelDesc desc;
    PopupInit init;
    int i;
    int selected;

    g_sceneWork_020c50e0 = work;
    SetStateFlagBits_020bc688(5, 0);
    MIi_CpuClearFast_01ff8740(0, work, sizeof(SceneWork));
    work->isClosing = 0;
    work->unk_D19C = 0;
    work->unk_D1B8 = 0;
    work->unk_D1E0 = 0;
    work->unk_D1BC = 0;
    work->unk_D1C0 = 0;
    work->unk_D1CC = 0;
    work->unk_D1D4 = 0;
    work->unk_D1D8 = 0;
    work->unk_D1DC = 0;
    for (i = 0; i < 30; i++) {
        if (IsGlobalPackedBitSet_02027304(i + 0xf1a)) {
            SetEntryFlag_020c22d4(0, i);
        }
    }
    for (i = 0; i < 8; i++) {
        if (IsGlobalPackedBitSet_02027304(i + 0xf3c)) {
            SetEntryFlag_020c22d4(2, i);
        }
    }
    func_ov093_020c0fb0(work);
    selected = work->selectedIndex;
    if (IsEntryFlagSet_020c22a4(4, selected)) {
        SetEntryFlag_020c22d4(5, selected);
    }
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    AcquireRecordSlot_02051d3c(9, 1);
    func_ov093_020bf67c(work);
    func_ov093_020bf880(work);
    func_ov093_020bf8e4(work);
    func_ov093_020bfac4(work);
    func_ov093_020c0100(work);
    func_ov093_020c05b8(work);
    func_ov093_020c1ca8(work);
    func_ov093_020c06ec(&data_ov093_020c4038, work);
    MIi_CpuCopyFast_01ff878c(&data_ov093_020c4064, &desc, sizeof(PanelDesc));
    desc.value = work->unk_D19C;
    func_ov093_020c06ec(&desc, work);
    func_ov093_020bfd60(-1, work);
    init.vramBase = work->vramBase;
    init.resources = work->resources;
    init.animSet = work->animSets[1];
    init.unk_0C = work->unk_CF00;
    work->popupHandle = func_ov093_020c3bdc(&init);
    InvokeForChannelOrBoth_0200110c(1, (u32)data_ov093_020c4d34, (int)func_ov093_020c2b04, 0);
    func_ov093_020c231c(1, work);
    return TRUE;
}



