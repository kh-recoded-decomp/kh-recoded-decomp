#include "nitro/types.h"

typedef struct {
    int archive;
    void *archiveTable;
    void *objectManager;
    int fontId;
} PopupManagerParams;

typedef struct {
    int currentEntry;
    int archives[2];
    u8 pad_0c[4];
    u8 archiveTable[0x6528 - 0x10];
    u8 objectManager[0xc9d4 - 0x6528];
    int fontId;
    u8 pad_c9d8[0xc9f4 - 0xc9d8];
    int values[5];
    void *popupManager;
    u8 pad_ca0c[0xcc00 - 0xca0c];
    int savedEntry;
    u8 pad_cc04[0xcc68 - 0xcc04];
    int mode;
    int modeStep;
    int modeTimer;
    u8 pad_cc74[0xcc7c - 0xcc74];
    BOOL altLayout;
} MenuScene;

extern MenuScene *data_ov091_020c3720;
extern const u8 data_ov091_020c2a30[];
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern int func_ov039_020bc828(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void AcquireMapLayout_020506dc(int a, int b);
extern void func_ov091_020bef9c(MenuScene *scene);
extern void func_ov091_020bf194(MenuScene *scene);
extern void LoadMenuGraphics_020bf200(MenuScene *scene);
extern void func_ov091_020bf410(MenuScene *scene);
extern void func_ov091_020bf788(MenuScene *scene);
extern void func_ov091_020bfc6c(const void *layout, MenuScene *scene);
extern void *func_ov091_020c279c(PopupManagerParams *params);
extern void UpdateEntryProgress_020c0448(MenuScene *scene);
extern void ComputeCompletionPercent_020c112c(MenuScene *scene);
extern void func_ov091_020c12b4(MenuScene *scene);
extern void func_ov091_020c1350(MenuScene *scene);
extern void func_ov091_020c1400(MenuScene *scene);
extern BOOL IsEntryFlagSet_020c16e8(int flagSet, int entryIndex);
extern void SetEntryFlag_020c1718(int flagSet, int entryIndex);
extern void SetListPanelSlotFlag_020bf918(int screen, int panelIndex, int value, MenuScene *scene);
extern void func_ov091_020bfbac(int screen, int panelIndex, BOOL value, MenuScene *scene);
extern void SetSceneMode_020c173c(int mode, MenuScene *scene);

BOOL InitRecordMenuScene_020beb20(MenuScene *scene)
{
    PopupManagerParams params;
    int i;
    int entry;

    data_ov091_020c3720 = scene;
    SetStateFlagBits_020bc688(5, 0);
    MIi_CpuClearFast_01ff8740(0, scene, sizeof(MenuScene));
    scene->currentEntry = func_ov039_020bc828();
    scene->mode = 0;
    scene->modeStep = 0;
    scene->modeTimer = 0;
    scene->altLayout = FALSE;
    if (IsGlobalPackedBitSet_02027304(0xbea) && !IsGlobalPackedBitSet_02027304(0xf4c)) {
        scene->altLayout = TRUE;
    }
    for (i = 0; i < 5; i++) {
        scene->values[i] = 0;
    }
    AcquireMapLayout_020506dc(0, 0);
    func_ov091_020bef9c(scene);
    func_ov091_020bf194(scene);
    LoadMenuGraphics_020bf200(scene);
    func_ov091_020bf410(scene);
    func_ov091_020bf788(scene);
    func_ov091_020bfc6c(data_ov091_020c2a30, scene);
    scene->currentEntry = func_ov039_020bc828();
    scene->savedEntry = scene->currentEntry;
    params.archive = scene->archives[0];
    params.archiveTable = scene->archiveTable;
    params.objectManager = scene->objectManager;
    params.fontId = scene->fontId;
    scene->popupManager = func_ov091_020c279c(&params);
    UpdateEntryProgress_020c0448(scene);
    ComputeCompletionPercent_020c112c(scene);
    func_ov091_020c12b4(scene);
    func_ov091_020c1350(scene);
    func_ov091_020c1400(scene);
    for (i = 0; i < 5; i++) {
        SetListPanelSlotFlag_020bf918(0, i + 1, IsEntryFlagSet_020c16e8(2, i), scene);
    }
    entry = scene->currentEntry;
    if (IsEntryFlagSet_020c16e8(2, entry)) {
        SetEntryFlag_020c1718(3, entry);
    }
    entry = scene->currentEntry;
    func_ov091_020bfbac(0, entry + 1, IsEntryFlagSet_020c16e8(3, entry) != FALSE, scene);
    SetSceneMode_020c173c(1, scene);
    return TRUE;
}
