#include "nitro/types.h"

typedef struct {
    s16 sceneId;
    s16 entryId;
    u8 kind;
    u8 pad_05[7];
} SceneArgs;

typedef struct {
    u8 pad_00[0x66c4];
    s32 flagA;
    s32 flagB;
} Panel;

extern SceneArgs data_02060850;
extern u8 data_ov000_02063798[];

extern void func_02026ee0(u32 mode);
extern void WriteGlobalPackedBits_02027360(u32 id, u32 bits, u32 value);
extern void SetGlobalPackedBit_02027320(u32 id);
extern void RebuildRecordCounters_02028e6c(void);
extern void SetupAllSelectionRecords_0204f85c(void);
extern void FillSelectionRecordFromGroup_0204f8dc(void);
extern void BuildSelectionEntryList_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);
extern void SetPendingScene_02025644(int scene, int arg);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void FinishTitlePanel_02062920(Panel *panel)
{
    func_02026ee0(1);
    data_02060850.sceneId = 100;
    data_02060850.entryId = -1;
    data_02060850.kind = 1;
    WriteGlobalPackedBits_02027360(0x3300, 8, 0);
    if (panel->flagA != 0) {
        SetGlobalPackedBit_02027320(0x1150);
    }
    if (panel->flagB != 0) {
        SetGlobalPackedBit_02027320(0x1151);
    }
    RebuildRecordCounters_02028e6c();
    SetupAllSelectionRecords_0204f85c();
    FillSelectionRecordFromGroup_0204f8dc();
    BuildSelectionEntryList_0204f98c();
    SyncSelectionRecordFromSlotEntry_0204fabc();
    func_0204fba0();
    SetPendingScene_02025644(2, 0);
    func_02007250(data_ov000_02063798, 0, 2);
    GXS_LoadBGPltt_020072b4(data_ov000_02063798, 0, 2);
    REG_DISPCNT &= ~0x1f00;
    REG_DB_DISPCNT &= ~0x1f00;
}
