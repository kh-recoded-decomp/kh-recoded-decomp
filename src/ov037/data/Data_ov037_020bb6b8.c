#include "nitro/types.h"

extern void AdvanceCommWhenReady_020ba91c(void);
extern void CloseCommAndRestoreRoom_020ba980(void);
extern void FinishCommSession_020ba7f0(void);
extern void MarkCommBusyWhenReady_020ba944(void);
extern void MarkCommChannelBusy_020ba73c(void);
extern void NotifyCommSlotIfReady_020ba874(void);
extern void ResetCommSlotWhenIdle_020ba8a8(void);
extern void StoreCommResultSlot_020ba8e4(void);
extern void SyncSessionCommFlags_020ba764(void);
extern void func_ov037_020ba90c(void);
extern void func_ov037_020baa3c(void);

void (*data_ov037_020bb6b8[11])(void) = {
    MarkCommChannelBusy_020ba73c,
    SyncSessionCommFlags_020ba764,
    FinishCommSession_020ba7f0,
    NotifyCommSlotIfReady_020ba874,
    ResetCommSlotWhenIdle_020ba8a8,
    StoreCommResultSlot_020ba8e4,
    func_ov037_020ba90c,
    AdvanceCommWhenReady_020ba91c,
    MarkCommBusyWhenReady_020ba944,
    CloseCommAndRestoreRoom_020ba980,
    func_ov037_020baa3c,
};
