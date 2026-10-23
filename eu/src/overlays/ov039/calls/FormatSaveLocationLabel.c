#include "nitro/types.h"

typedef struct RecordSaveData {
    u8 pad_0000[0x28d4];
    s8 worldId;
    s8 areaId;
} RecordSaveData;

extern u16 gGridLabelBuffer[64];
extern RecordSaveData *data_0205fe0c;
extern const u16 sGridLabelSpacedSeparator[];
extern const u16 sGridLabelSeparator[];
extern const u16 sGridLabelJoinedFormat[];
extern const u16 sGridLabelSingleFormat[];

extern int GetMenuSelection(void);
extern u32 GetRuntimeStateFlags(void);
extern int func_ov001_020644b0(void);
extern int GetLanguageIndex(void);
extern const u16 *GetGridTableValue(int worldId, int areaId);
extern int OS_SNPrintf_0202e094(u16 *dst, u32 len, const u16 *fmt, ...);

static inline BOOL IsInRoom900(void)
{
    return func_ov001_020644b0() == 900;
}

u16 *FormatSaveLocationLabel(RecordSaveData *save)
{
    int areaId;
    int worldId;
    BOOL joined;

    if (GetMenuSelection() != 3) {
        if (!(GetRuntimeStateFlags() & 0x4000) && IsInRoom900()) {
            OS_SNPrintf_0202e094(gGridLabelBuffer, 0x40, sGridLabelSingleFormat,
                                GetGridTableValue(8, -1));
            goto done;
        }
        if (GetRuntimeStateFlags() == 0x4000 && save == data_0205fe0c) {
            gGridLabelBuffer[0] = 0;
            goto done;
        }
    }

    areaId = save->areaId;
    worldId = save->worldId;
    u32 location = (u32)areaId | ((u32)worldId << 16);

    /* Keep the range dispatch separate from the area-only cases. */
    if (location > 0x2000a) {
        goto higherLocation;
    }
    joined = TRUE;
    if (location >= 0x2000a) {
        goto languageRule;
    }
    if (location > 3) {
        goto formatLabel;
    }
    if (location < 1) {
        goto formatLabel;
    }
    switch (location) {
    case 1:
    case 2:
    case 3:
        goto singleLocationLabel;
    }
    goto formatLabel;

higherLocation:
    joined = TRUE;
    if (location > 0x2000b) {
        goto highestLocation;
    }
    if (location == 0x2000b) {
        goto languageRule;
    }
    goto formatLabel;

highestLocation:
    if (location != 0x2000c) {
        goto formatLabel;
    }
languageRule:
    /* World 2, areas 10-12 omit the world name in languages 4 and 5. */
    joined = GetLanguageIndex() != 4 && GetLanguageIndex() != 5;
    goto formatLabel;

singleLocationLabel:
    joined = FALSE;

formatLabel:
    if (joined) {
        const u16 *worldName = GetGridTableValue(worldId, -1);
        const u16 *areaName = GetGridTableValue(worldId, areaId);

        OS_SNPrintf_0202e094(gGridLabelBuffer, 0x40, sGridLabelJoinedFormat, worldName,
                            GetLanguageIndex() == 2 ? sGridLabelSpacedSeparator : sGridLabelSeparator,
                            areaName);
    } else {
        OS_SNPrintf_0202e094(gGridLabelBuffer, 0x40, sGridLabelSingleFormat,
                            GetGridTableValue(worldId, areaId));
    }
done:
    return gGridLabelBuffer;
}
