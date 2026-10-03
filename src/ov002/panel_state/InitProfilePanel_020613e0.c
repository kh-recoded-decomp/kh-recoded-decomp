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
extern u8 data_ov002_0206c35c[];
extern SharedSettings data_0206085c;
extern u16 data_02060878[];
extern u16 data_0206088e[];
extern u8 data_ov027_020ba380[];
extern char OverlayId27_0000001b[];

extern PanelState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8740(int value, void *dst, u32 size);
extern s32 func_0202a754(void);
extern int func_0204f58c(short *record, short *limits);
extern void func_02029f78(int processor, int overlay_id);
extern void func_ov002_02062938(void);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel);
extern void AcquireRecordManager_02051c80(void);
extern void CopySharedSettings_02004ae4(unsigned char *r0);
extern void CopyWideStringLowercase_02066324(u16 *dst, const u16 *src);
extern u16 *CopyWideString_02066394(u16 *dst, const u16 *src);
extern BOOL CensorBannedWords_02066130(u16 *out, void *unused, const u16 *text);
extern void QueueSoundCommandForArc_0204d670(int command);
extern int func_ov002_02066c78(u32 arg0, int arg1, int arg2, int arg3);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_0202b5d4(void);
extern void SetSelectionIfChanged_0204d73c(int selection);
extern void func_ov002_02066c44(void);
extern void func_ov002_02066c68(int language);
extern void SwitchPanelMode_02062cb8(int mode);
extern void AcquireRecordSlot_02051d3c(int slot, int flag);
extern void func_ov002_020617e4(void);
extern void func_ov002_0206162c(void);

void *InitProfilePanel_020613e0(BOOL resumed)
{
    PanelState *state;

    state = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov002_0206c460 = state;
    func_01ff8740(0, state, 0x130);
    state->heapId = func_0202a754();
    state->selection = -1;
    func_0204f58c(state->record, NULL);
    func_02029f78(0, (int)OverlayId27_0000001b);
    func_ov002_02062938();
    InvokeForChannelOrBoth_0200110c(1, (u32)data_ov002_0206c35c, (int)func_ov002_020617e4, 0);
    AcquireRecordManager_02051c80();
    if (!data_0206085c.censored) {
        u16 nickname[11] = {0};
        u16 message[27] = {0};
        OwnerProfile profile;

        CopySharedSettings_02004ae4((unsigned char *)&profile);
        CopyWideStringLowercase_02066324(nickname, profile.nickname);
        CopyWideStringLowercase_02066324(message, profile.message);
        CopyWideString_02066394(data_02060878, profile.nickname);
        CopyWideString_02066394(data_0206088e, profile.message);
        CensorBannedWords_02066130(data_02060878, (void *)0x16, nickname);
        CensorBannedWords_02066130(data_0206088e, (void *)0x36, message);
        data_0206085c.censored = TRUE;
    }
    QueueSoundCommandForArc_0204d670(2);
    if (func_ov002_02066c78(0x12, 0, 0, 0) == 0) {
        func_ov002_02066c78(0x80000017, 1, 0, 0);
    }
    state->task = func_0202a448(data_ov027_020ba380, NULL);
    func_0202b5d4();
    if (!resumed) {
        SetSelectionIfChanged_0204d73c(1);
        func_ov002_02066c44();
        state->isNewGame = TRUE;
        SwitchPanelMode_02062cb8(0);
    } else {
        func_ov002_02066c68(data_0206085c.language);
        state->isNewGame = FALSE;
        SwitchPanelMode_02062cb8(3);
    }
    AcquireRecordSlot_02051d3c(0xb, 0);
    AcquireRecordSlot_02051d3c(9, 1);
    return func_ov002_0206162c;
}
