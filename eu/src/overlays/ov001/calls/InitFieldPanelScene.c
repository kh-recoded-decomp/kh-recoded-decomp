#include "nitro/types.h"

typedef struct {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct {
    void *archive;
    u8 pad_04[0x1c - 0x04];
    u16 *name;
    MessageSet messages;
    u32 unk_2c;
    s32 phase;
    u8 pad_34[0x50 - 0x34];
    s32 selection;
    u8 pad_54[0x58 - 0x54];
    s32 fadeSpeed;
    u8 file[0xa4 - 0x5c];
    u8 overlayInfo[0xd4 - 0xa4];
    void *overlayData;
    s32 waitFrames;
    s32 waitReload;
    s32 brightness;
    void *graphics[4];
    u8 pad_f4[0x102 - 0xf4];
    u8 language;
    u8 formationType;
    u8 pad_104[0x108 - 0x104];
    u32 sessionFlags;
    u8 pad_10c[0x114 - 0x10c];
} PanelScene;

typedef struct {
    u32 unk_00 : 12;
    u32 panelStyle : 2;
} SessionStateFlags;

typedef void *(*PanelStep)(void);

extern PanelScene *data_ov001_020a04e8;
extern u8 *data_0205fe0c;
extern u8 data_ov025_020b7748[];
extern u8 data_ov026_020b5ae0[];
extern u32 OVERLAY_25_ID[1];
extern u32 OVERLAY_26_ID[1];

extern void SetDisplaySetting(int value);
extern void AcquireRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void ReleaseRecordManager(void);
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, u8 val, u32 size);
extern u8 GetPrimarySelectionByte1E(void);
extern void BuildEntryNameList(PanelScene *panel);
extern void LoadModeNameAndMessages(PanelScene *panel);
extern void FS_InitFile(void *file);
extern BOOL FS_LoadOverlay(u32 target, u32 overlayId);
extern int FS_UnloadOverlay(u32 target, u32 overlayId);
extern void *Obj_CreateWithTailWork(void *data, int size);
extern void PXI_Init_0202a64c(void *archive);
extern void *LookupChannelEntry(int index);
extern void func_ov001_0207a920(PanelScene *panel, u32 overlayId);
extern void *UpdatePanelScene(void);

PanelStep InitFieldPanelScene(void)
{
    PanelScene *panel;
    int i;

    SetDisplaySetting(1);
    AcquireRecordManager();
    AcquireRecordSlot(1, 1);
    panel = NNSi_FndGetCurrentRootHeap();
    data_ov001_020a04e8 = panel;
    i = 0;
    MI_CpuFill8(panel, 0, sizeof(PanelScene));
    panel->formationType = 2;
    panel->selection = -1;
    panel->language = GetPrimarySelectionByte1E();
    panel->fadeSpeed = 6;
    panel->sessionFlags = ((SessionStateFlags *)(data_0205fe0c + 0x2878))->panelStyle;
    BuildEntryNameList(panel);
    LoadModeNameAndMessages(panel);
    FS_InitFile(panel->file);
    FS_LoadOverlay(0, (u32)OVERLAY_25_ID);
    panel->archive = Obj_CreateWithTailWork(data_ov025_020b7748, -1);
    do {
        panel->graphics[i] = LookupChannelEntry(i);
        i++;
    } while (i < 4);
    PXI_Init_0202a64c(panel->archive);
    panel->archive = NULL;
    FS_UnloadOverlay(0, (u32)OVERLAY_25_ID);
    panel->overlayData = data_ov026_020b5ae0;
    panel->phase = 2;
    panel->waitFrames = 4;
    panel->waitReload = panel->waitFrames;
    func_ov001_0207a920(panel, (u32)OVERLAY_26_ID);
    ReleaseRecordSlot(1);
    ReleaseRecordManager();
    return (PanelStep)UpdatePanelScene;
}
