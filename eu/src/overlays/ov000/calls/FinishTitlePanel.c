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

extern void InitSaveData(u32 mode);
extern void WriteGlobalPackedBits(u32 id, u32 bits, u32 value);
extern void SetGlobalPackedBit(u32 id);
extern void RebuildRecordCounters(void);
extern void SetupAllSelectionRecords(void);
extern void FillSelectionRecordFromGroup(void);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);
extern void func_0204fbb4(void);
extern void SetPendingScene(int scene, int arg);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void FinishTitlePanel(Panel *panel)
{
    InitSaveData(1);
    data_02060850.sceneId = 100;
    data_02060850.entryId = -1;
    data_02060850.kind = 1;
    WriteGlobalPackedBits(0x3300, 8, 0);
    if (panel->flagA != 0) {
        SetGlobalPackedBit(0x1150);
    }
    if (panel->flagB != 0) {
        SetGlobalPackedBit(0x1151);
    }
    RebuildRecordCounters();
    SetupAllSelectionRecords();
    FillSelectionRecordFromGroup();
    BuildSelectionEntryList();
    SyncSelectionRecordFromSlotEntry();
    func_0204fbb4();
    SetPendingScene(2, 0);
    GX_LoadBGPltt(data_ov000_02063798, 0, 2);
    GXS_LoadBGPltt(data_ov000_02063798, 0, 2);
    REG_DISPCNT &= ~0x1f00;
    REG_DB_DISPCNT &= ~0x1f00;
}
