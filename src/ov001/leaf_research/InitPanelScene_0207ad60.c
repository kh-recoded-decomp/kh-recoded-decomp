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

extern PanelScene *g_panelScene_020a04c8;
extern u8 *data_0205fe0c;
extern u8 data_ov025_020b7728[];
extern u8 data_ov026_020b5ac0[];
extern u32 OVERLAY_25_ID_00000019[1];
extern u32 OVERLAY_26_ID_0000001a[1];

extern void SetDisplaySetting_02029f28(int value);
extern void func_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_02051cdc(void);
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void MI_CpuFill8_01ff8830(void *dst, u8 val, u32 size);
extern u8 func_02050514(void);
extern void func_ov001_0207aa6c(PanelScene *panel);
extern void LoadModeNameAndMessages_0207ab10(PanelScene *panel);
extern void func_0200b394(void *file);
extern BOOL func_0200bd64(u32 target, u32 overlayId);
extern int func_0200bdb8(u32 target, u32 overlayId);
extern void *func_0202a47c(void *data, int size);
extern void func_0202a638(void *archive);
extern void *func_ov025_020b6270(int index);
extern void func_ov001_0207a920(PanelScene *panel, u32 overlayId);
extern void *func_ov001_0207aff0(void);

PanelStep InitPanelScene_0207ad60(void)
{
    PanelScene *panel;
    int i;

    SetDisplaySetting_02029f28(1);
    func_02051c80();
    AcquireRecordSlot_02051d3c(1, 1);
    panel = NNSi_FndGetCurrentRootHeap_0202a764();
    g_panelScene_020a04c8 = panel;
    i = 0;
    MI_CpuFill8_01ff8830(panel, 0, sizeof(PanelScene));
    panel->formationType = 2;
    panel->selection = -1;
    panel->language = func_02050514();
    panel->fadeSpeed = 6;
    panel->sessionFlags = ((SessionStateFlags *)(data_0205fe0c + 0x2878))->panelStyle;
    func_ov001_0207aa6c(panel);
    LoadModeNameAndMessages_0207ab10(panel);
    func_0200b394(panel->file);
    func_0200bd64(0, (u32)OVERLAY_25_ID_00000019);
    panel->archive = func_0202a47c(data_ov025_020b7728, -1);
    do {
        panel->graphics[i] = func_ov025_020b6270(i);
        i++;
    } while (i < 4);
    func_0202a638(panel->archive);
    panel->archive = NULL;
    func_0200bdb8(0, (u32)OVERLAY_25_ID_00000019);
    panel->overlayData = data_ov026_020b5ac0;
    panel->phase = 2;
    panel->waitFrames = 4;
    panel->waitReload = panel->waitFrames;
    func_ov001_0207a920(panel, (u32)OVERLAY_26_ID_0000001a);
    ReleaseRecordSlot_02051dfc(1);
    func_02051cdc();
    return (PanelStep)func_ov001_0207aff0;
}
