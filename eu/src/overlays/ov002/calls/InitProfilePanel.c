#include "nitro/types.h"
#include "src/overlays/ov027/CapturedTouch.h"

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

extern PanelState *gOv002ProfilePanelWork;
extern u8 sOv002_WXCVB_0206c35c[];
extern SharedSettings data_0206085c;
extern u16 gCachedOwnerNickname[];
extern u16 gCachedOwnerMessageStorage[];
extern char OVERLAY_27_ID[];

extern PanelState *GetRunningTaskWork(void);
extern void MIi_CpuClearFast(int value, void *dst, u32 size);
extern s32 GetCurrentTaskObject(void);
extern int InitKeyRepeatState(short *record, short *limits);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlay_id);
extern void ReloadPanelResources(void);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);
extern void AcquireRecordManager(void);
extern void OS_GetOwnerInfo(unsigned char *r0);
extern void CopyWideStringLowercase(u16 *dst, const u16 *src);
extern u16 *CopyWideString(u16 *dst, const u16 *src);
extern BOOL CensorBannedWords(u16 *out, void *unused, const u16 *text);
extern void QueueSoundCommandForArc(int command);
extern int DispatchContextCommand(u32 arg0, int arg1, int arg2, int arg3);
extern void *CreateTaskObject(void *descriptor, void *userData);
extern void StartTouchSamplingRing(void);
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

    state = GetRunningTaskWork();
    gOv002ProfilePanelWork = state;
    MIi_CpuClearFast(0, state, 0x130);
    state->heapId = GetCurrentTaskObject();
    state->selection = -1;
    InitKeyRepeatState(state->record, NULL);
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
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
        CopyWideString(gCachedOwnerNickname, profile.nickname);
        CopyWideString(gCachedOwnerMessageStorage, profile.message);
        CensorBannedWords(gCachedOwnerNickname, (void *)0x16, nickname);
        CensorBannedWords(gCachedOwnerMessageStorage, (void *)0x36, message);
        data_0206085c.censored = TRUE;
    }
    QueueSoundCommandForArc(2);
    if (DispatchContextCommand(0x12, 0, 0, 0) == 0) {
        DispatchContextCommand(0x80000017, 1, 0, 0);
    }
    state->task = CreateTaskObject(&gCapturedTouchTaskDescriptor, NULL);
    StartTouchSamplingRing();
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
