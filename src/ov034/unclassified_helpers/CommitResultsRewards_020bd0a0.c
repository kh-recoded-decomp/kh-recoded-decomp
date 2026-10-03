#include "nitro/types.h"

typedef struct ResultsParams {
    s32 earnedAmount;
    u8 pad_04[0x1e];
    u8 worldId;
    u8 pad_23;
    u8 unlockedRank;
    u8 pad_25[0xc];
    s8 slotLevels[0x24];
    s8 slotIndex;
    u8 pad_56[0x19];
    u8 committed;
} ResultsParams;

typedef struct ResultsScreen {
    ResultsParams *params;
    void *work;
} ResultsScreen;

extern ResultsScreen g_resultsScreen_020c0f80;
extern void ClearSessionSlots_02063b80(void);
extern void func_ov001_020876cc(void);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void ResourceCache_FreeAll_02086df0(void);
extern void AddSessionCounter_02063a80(int index, int amount);
extern void func_ov001_02063130(int level, int flag);
extern void ClearFieldCounters_02064dc8(void);

void CommitResultsRewards_020bd0a0(void)
{
    ClearSessionSlots_02063b80();
    func_ov001_020876cc();
    WriteSessionPackedBits_0206459c(0x3880, 0x660, 0);
    ResourceCache_FreeAll_02086df0();
    AddSessionCounter_02063a80(1, g_resultsScreen_020c0f80.params->earnedAmount);
    func_ov001_02063130(g_resultsScreen_020c0f80.params->slotLevels[g_resultsScreen_020c0f80.params->slotIndex] + 1, 1);
    g_resultsScreen_020c0f80.params->committed = 1;
    ClearFieldCounters_02064dc8();
    if (g_resultsScreen_020c0f80.params->worldId == 0x15 && g_resultsScreen_020c0f80.params->unlockedRank == 0xd) {
        WriteSessionPackedBits_0206459c(0x380c, 1, 1);
    }
}
