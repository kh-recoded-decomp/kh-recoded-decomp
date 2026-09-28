#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
} CardThreadState;

extern CardThreadState g_cardThreadState_0205fe00;
extern void *CARD_UnlockBackup_020091ac(int id);
extern void CardUnlockAfterKeyShare_020091b8(int id);
extern int ReadCardBackupSync_02026b00(u32 src, void *dst, u32 length);
extern BOOL FormatCardBackup_02026d30(void);
extern void InitSaveData_02026ee0(u32 mode);

BOOL FormatSaveData_02026ea0(void)
{
    u32 probe;
    BOOL success;

    CARD_UnlockBackup_020091ac(g_cardThreadState_0205fe00.resourceId);
    success = TRUE;
    if (ReadCardBackupSync_02026b00(0, &probe, 1) != 0 || FormatCardBackup_02026d30() == 0) {
        success = FALSE;
    }
    CardUnlockAfterKeyShare_020091b8(g_cardThreadState_0205fe00.resourceId);
    InitSaveData_02026ee0(1);
    return success;
}
