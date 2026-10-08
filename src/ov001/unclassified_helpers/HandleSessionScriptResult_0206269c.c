#include "nitro/types.h"

typedef struct RequestFlags {
    u32 unk_0 : 7;
    u32 stateChanged : 1;
    u32 unk_8 : 24;
} RequestFlags;

typedef struct SessionRequest {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 command;
    s16 unk_08;
    s16 unk_0A;
    RequestFlags flags;
} SessionRequest;

typedef struct Session {
    u8 pad_0000[0x208];
    SessionRequest request;
    u8 pad_0218[0x1cf8];
    u8 script[0x8e1];
    u8 unk_27F1_0 : 1;
    u8 unk_27F1_1 : 3;
    u8 unk_27F1_4 : 1;
    u8 unk_27F1_5 : 3;
    u8 pad_27f2[7];
    u8 trackId;
    u8 pad_27fa[2];
    s8 unk_27FC;
    u8 trackPending : 1;
    u8 unk_27FD_1 : 7;
    u8 pad_27fe[0xa];
    s8 state;
    u8 pad_2809[0x9b];
    s8 mode;
    u8 pad_28a5[0x10b];
    u32 unk_29B0;
#ifndef SESSION_FLAGS_29B4_QUALIFIER
#define SESSION_FLAGS_29B4_QUALIFIER
#endif
    SESSION_FLAGS_29B4_QUALIFIER u8 unk_29B4_0 : 1;
    SESSION_FLAGS_29B4_QUALIFIER u8 unk_29B4_1 : 1;
    SESSION_FLAGS_29B4_QUALIFIER u8 unk_29B4_2 : 1;
    SESSION_FLAGS_29B4_QUALIFIER u8 unk_29B4_3 : 5;
} Session;

extern Session *data_ov001_020a0460;
extern u32 data_02060848;

extern void func_020257e4(void *channel);
extern void func_0204d7f4(int value);
extern s32 SetSessionState_02063200(s32 newState, s32 mode);
extern void StoreSessionDifficultyPreset_0206452c(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void ResetTrackState_02062cf8(void);
extern void func_ov001_020630bc(void);
extern void func_020273d4(void);
extern void func_ov001_02063a58(u8 value);
extern void ReleaseLowIdTaskNodes_02069194(void);
extern void SetGlobalStateValue_0209d184(u32 value);

s32 HandleSessionScriptResult_0206269c(void) {
    Session *session = data_ov001_020a0460;
    SessionRequest *request = &session->request;
    s32 nextStep = -1;

    func_020257e4(session->script);

    if (request->unk_08 >= 0) {
        func_0204d7f4(0x14);
        nextStep = 12;
    } else {
        switch (request->command) {
        case -2:
            SetSessionState_02063200(5, 1);
            request->flags.stateChanged = 1;
            StoreSessionDifficultyPreset_0206452c();
            break;
        case -4:
            SetSessionState_02063200(11, 1);
            request->flags.stateChanged = 1;
            break;
        case -3:
            SetSessionState_02063200(9, session->mode);
            request->flags.stateChanged = 1;
            if (func_ov001_020645c8(0x3525)) {
                session->trackPending = 1;
            }
            if (data_ov001_020a0460->unk_27FC != -1) {
                session->trackId = 0xff;
            }
            break;
        case -5:
            SetSessionState_02063200(12, 1);
            request->flags.stateChanged = 1;
            break;
        default:
            nextStep = 0;
            break;
        }
    }

    if (request->flags.stateChanged) {
        if (!session->trackPending) {
            func_0204d7f4(0x14);
            ResetTrackState_02062cf8();
        }
        nextStep = 3;
        session->trackPending = 0;
    }

    switch (session->state) {
    case 0:
    case 4:
    case 6:
    case 7:
    case 10:
        request->unk_0A = request->unk_02;
        break;
    }

    session->unk_27F1_0 = 0;
    session->unk_27F1_4 = 0;
    session->unk_29B4_0 = 0;
    session->unk_29B4_1 = 0;
    session->unk_29B4_2 = 0;
    session->unk_29B0 = 0;

    if (!func_ov001_020645c8(0x1a05)) {
        func_ov001_020630bc();
        func_020273d4();
    }
    func_ov001_02063a58(0);
    ReleaseLowIdTaskNodes_02069194();
    SetGlobalStateValue_0209d184(0);
    data_02060848 = 0;
    return nextStep;
}
