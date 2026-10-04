#include "nitro/types.h"

typedef struct {
    u8 pad0[0x134];
    int group;
    int pad138;
    int subPage;
    u8 pad140[0x10];
    int touchMode;
    int sliderActive;
    u8 pad158[0x1c];
    u8 tileTable[0x6c];
    u8 sourceBlock[8];
} RecordPanel;

extern u8 *data_0205fe0c;
extern BOOL func_ov039_020bc0ec(void);
extern void *func_ov039_020bc1bc(void);
extern void *func_ov039_020bc1cc(void);
extern void SetWidgetRootDpadEnabled_020b9874(void *root, BOOL enabled);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern s64 OS_GetTick_02003fd4(void);
extern s64 GetCardThreadStartTick_0202726c(void);
extern int CopySourceBlock_020b9f7c(void *dst);
extern void ClearScreenLayerDirty_020bc128(int layerId);
extern void func_ov027_020b9e60(void *table);
extern void func_ov086_020bed2c(RecordPanel *panel, int mode);
extern void func_ov086_020c1600(RecordPanel *panel);
extern BOOL func_ov086_020c1674(RecordPanel *panel, int mode);
extern void func_ov086_020c1828(RecordPanel *panel);
extern void func_ov086_020c1a28(RecordPanel *panel, int seconds);

void UpdateRecordPanelInput_020c1ed4(RecordPanel *panel)
{
    int group;
    u64 playSeconds;

    if (panel->touchMode) {
        if (!func_ov039_020bc0ec()) {
            panel->touchMode = 0;
            func_ov086_020bed2c(panel, 0);
        } else if (panel->sliderActive) {
            func_ov086_020c1600(panel);
        } else if (!func_ov086_020c1674(panel, 0)) {
            group = panel->group;
            if (group != 7) {
                if ((group == 6 && panel->subPage == 1) || (group != 6 && panel->subPage != 0)) {
                    func_ov086_020c1828(panel);
                }
            }
        }
    } else if (func_ov039_020bc0ec() || func_ov086_020c1674(panel, 1)) {
        panel->touchMode = 1;
        func_ov086_020bed2c(panel, 1);
        SetWidgetRootDpadEnabled_020b9874(func_ov039_020bc1bc(), 0);
        SetWidgetRootDpadEnabled_020b9874(func_ov039_020bc1cc(), 1);
        SetPrimaryElementEnabled_020bc054(0);
        SetSecondaryElementEnabled_020bc084(1);
    }
    playSeconds = *(u32 *)(data_0205fe0c + 0x28c8) + (u64)(OS_GetTick_02003fd4() - GetCardThreadStartTick_0202726c()) * 64 / 0x1ff6210;
    func_ov086_020c1a28(panel, playSeconds);
    CopySourceBlock_020b9f7c(panel->sourceBlock);
    ClearScreenLayerDirty_020bc128(0x19);
    ClearScreenLayerDirty_020bc128(0x1a);
    func_ov027_020b9e60(panel->tileTable);
}
