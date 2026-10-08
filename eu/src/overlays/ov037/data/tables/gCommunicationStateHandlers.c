#include "nitro/types.h"

extern void MarkCommChannelBusy(void); /* MarkCommChannelBusy */
extern void SyncSessionCommFlags(void); /* SyncSessionCommFlags */
extern void FinishCommSession(void); /* FinishCommSession */
extern void NotifyCommSlotIfReady(void); /* NotifyCommSlotIfReady */
extern void ResetCommSlotWhenIdle(void); /* ResetCommSlotWhenIdle */
extern void StoreCommResultSlot(void); /* StoreCommResultSlot */
extern void UpdateMenuSelectionAndReturnState7(void);
extern void AdvanceCommWhenReady(void); /* AdvanceCommWhenReady */
extern void MarkCommBusyWhenReady(void); /* MarkCommBusyWhenReady */
extern void CloseCommAndRestoreRoom(void); /* CloseCommAndRestoreRoom */
extern void FinishCommunicationState(void);

void (*gCommunicationStateHandlers[11])(void) = {
    MarkCommChannelBusy, /* MarkCommChannelBusy */
    SyncSessionCommFlags, /* SyncSessionCommFlags */
    FinishCommSession, /* FinishCommSession */
    NotifyCommSlotIfReady, /* NotifyCommSlotIfReady */
    ResetCommSlotWhenIdle, /* ResetCommSlotWhenIdle */
    StoreCommResultSlot, /* StoreCommResultSlot */
    UpdateMenuSelectionAndReturnState7,
    AdvanceCommWhenReady, /* AdvanceCommWhenReady */
    MarkCommBusyWhenReady, /* MarkCommBusyWhenReady */
    CloseCommAndRestoreRoom, /* CloseCommAndRestoreRoom */
    FinishCommunicationState,
};
