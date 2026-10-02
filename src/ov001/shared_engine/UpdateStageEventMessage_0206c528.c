#include "nitro/types.h"

typedef struct EventInfo {
    u16 messageId;
    u16 isMessage : 1;
    u16 isTicker : 1;
    u16 reserved : 14;
    u8 pad_04[0x18];
    u32 tickerMode;
    u32 tickerValue;
} EventInfo;

typedef struct PendingRequest {
    s32 unk_00;
    s32 handle;
    s32 active;
} PendingRequest;

typedef struct Manager {
    u8 pad_00[0x3c];
    PendingRequest request;
} Manager;

extern Manager *g_manager_020a0484;

extern int IsStageEventReady_02087c78(u16 id);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern BOOL func_ov001_02087960(u16 id, EventInfo *info);
extern s32 func_ov001_02063a38(void);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern void ShowFieldMessageLine_0207163c(u16 tickerMode, u32 tickerValue, int messageId, BOOL resetTicker);
extern void HideFieldMessageLine_0207166c(void);
extern void ResetPendingRequest_0206c614(void);
extern void StageRecord_SetFlagBit2_02087d24(u16 id);
extern void *func_ov001_02071690(u16 id);

void UpdateStageEventMessage_0206c528(int id)
{
    PendingRequest *request = &g_manager_020a0484->request;
    EventInfo info;
    BOOL reset;

    switch (request->active) {
    case 0:
        if (id != -1 && IsStageEventReady_02087c78(id)) {
            reset = FALSE;
            GetBoundedEntryField_0206db5c(0);
            if (func_ov001_02087960(id, &info)) {
                if ((!info.isTicker || info.isMessage) && func_ov001_02063a38() != 6) {
                    if (IsPlayerEntryFlagSet_02050014(0, 9)) {
                        reset = TRUE;
                    }
                    ShowFieldMessageLine_0207163c(info.tickerMode, (u16)info.tickerValue, info.messageId, reset);
                } else {
                    HideFieldMessageLine_0207166c();
                }
                request->handle = id;
                request->active = 1;
            }
        }
        break;
    case 1:
        if (id == -1) {
            id = request->handle;
        }
        if (!IsStageEventReady_02087c78(id)) {
            ResetPendingRequest_0206c614();
            return;
        }
        StageRecord_SetFlagBit2_02087d24(id);
        if (id != request->handle) {
            request->active = 0;
            UpdateStageEventMessage_0206c528(id);
            return;
        }
        if (func_ov001_02087960(id, &info)) {
            func_ov001_02071690(info.tickerMode);
        }
        break;
    }
}
