#include "nitro/types.h"

typedef struct {
    u8 header[4];
    u16 nickname[12];
    u16 message[26];
    u16 nicknameLength;
    u16 messageLength;
} OwnerProfile;

typedef struct {
    u8 pad00[0x13];
    s8 language;
    u8 pad14[0x54];
    u8 censored : 1;
} SharedSettings;

typedef struct {
    s32 heapId;
    void *task;
    s32 selection;
    u8 pad0c[5];
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 isNewGame : 1;
    short record[13];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern u8 sOv002_WXCVB_0206c35c[];
extern SharedSettings data_0206085c;
extern u16 data_02060878[];
extern u16 data_0206088e[];
extern u8 data_ov027_020ba3a0[];
extern char OVERLAY_27_ID[];

extern PanelState *NNSi_FndGetCurrentRootHeap(void);
extern void MIi_CpuClearFast(int value, void *dst, u32 size);
extern s32 func_0202a768(void);
extern int func_0204f5a0(short *record, short *limits);
extern void func_02029f8c(int processor, int overlay_id);
extern void ReloadPanelResources(void);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);
extern void AcquireRecordManager(void);
extern void OS_GetOwnerInfo(unsigned char *r0);
extern void CopyWideStringLowercase(u16 *dst, const u16 *src);
extern u16 *CopyWideString(u16 *dst, const u16 *src);
extern BOOL CensorBannedWords(u16 *out, void *unused, const u16 *text);
extern void QueueSoundCommandForArc(int command);
extern int DispatchContextCommand(u32 arg0, int arg1, int arg2, int arg3);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void func_0202b5e8(void);
extern void SetSelectionIfChanged(int selection);
extern void ResetContextCommandFlag(void);
extern void SetContextCommandFlag(int language);
extern void SwitchPanelMode(int mode);
extern void AcquireRecordSlot(int slot, int flag);
extern void RunPanelDispatchAction(void);
extern void UpdatePanelState(void);

void *InitProfilePanel(BOOL resumed)
{
    PanelState *state;

    state = NNSi_FndGetCurrentRootHeap();
    data_ov002_0206c460 = state;
    MIi_CpuClearFast(0, state, 0x130);
    state->heapId = func_0202a768();
    state->selection = -1;
    func_0204f5a0(state->record, NULL);
    func_02029f8c(0, (int)OVERLAY_27_ID);
    ReloadPanelResources();
    InvokeForChannelOrBoth(1, (u32)sOv002_WXCVB_0206c35c, (int)RunPanelDispatchAction, 0);
    AcquireRecordManager();
    if (!data_0206085c.censored) {
        u16 nickname[11] = {0};
        u16 message[27] = {0};
        OwnerProfile profile;

        OS_GetOwnerInfo((unsigned char *)&profile);
        CopyWideStringLowercase(nickname, profile.nickname);
        CopyWideStringLowercase(message, profile.message);
        CopyWideString(data_02060878, profile.nickname);
        CopyWideString(data_0206088e, profile.message);
        CensorBannedWords(data_02060878, (void *)0x16, nickname);
        CensorBannedWords(data_0206088e, (void *)0x36, message);
        data_0206085c.censored = TRUE;
    }
    QueueSoundCommandForArc(2);
    if (DispatchContextCommand(0x12, 0, 0, 0) == 0) {
        DispatchContextCommand(0x80000017, 1, 0, 0);
    }
    state->task = func_0202a45c(data_ov027_020ba3a0, NULL);
    func_0202b5e8();
    if (!resumed) {
        SetSelectionIfChanged(1);
        ResetContextCommandFlag();
        state->isNewGame = TRUE;
        SwitchPanelMode(0);
    } else {
        SetContextCommandFlag(data_0206085c.language);
        state->isNewGame = FALSE;
        SwitchPanelMode(3);
    }
    AcquireRecordSlot(0xb, 0);
    AcquireRecordSlot(9, 1);
    return UpdatePanelState;
}
