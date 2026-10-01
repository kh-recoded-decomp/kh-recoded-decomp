#include "nitro/types.h"

typedef struct SessionRequest {
    s16 resultId;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 exitKind;
    s16 unk_0A;
} SessionRequest;

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 bit6 : 1;
    u32 unk_7 : 25;
} SessionFlags;

typedef struct SubOverlayWork {
    u8 pad_00[0xc];
    void (*finish)(int arg);
    BOOL (*poll)(void);
    void (*shutdown)(void);
    u8 pad_18[0x18];
} SubOverlayWork;

typedef struct Session {
    u8 pad_0000[0x1b];
    u8 exitRequested;
    u8 pad_001c[0x208 - 0x1c];
    SessionRequest request;
    SessionFlags flags;
    u8 pad_0218[0x20e0 - 0x218];
    s32 scriptResult;
    u8 pad_20e4[0x2738 - 0x20e4];
    u8 unk_2738;
    u8 pad_2739[0x280c - 0x2739];
    SubOverlayWork work;
    u8 pad_283c[0x28a4 - 0x283c];
    s8 finishArg;
} Session;

extern Session *data_ov001_020a0460;
extern BOOL func_ov001_020645c8(u32 value);
extern void ReleaseSessionHandle_02062c98(Session *session, BOOL flush);
extern s32 RunSessionScriptFrame_02063638(void);
extern void func_ov001_020631e4(int request);
extern void func_ov001_02062cd4(Session *session);
extern void func_ov001_020630e4(void);

s32 StepSessionScriptOrAbort_020625b8(void) {
    Session *session = data_ov001_020a0460;
    SubOverlayWork *work = &session->work;
    s32 nextState = -1;
    s32 status;

    if (func_ov001_020645c8(0x3637) && session->flags.bit6 && session->request.unk_06 == -3) {
        ReleaseSessionHandle_02062c98(session, FALSE);
        session->unk_2738 = 0;
        return 4;
    }
    status = RunSessionScriptFrame_02063638();
    if (status >= 0) {
        switch (status) {
        case 2:
            data_ov001_020a0460->exitRequested = 1;
            nextState = 9;
            break;
        case 1:
            func_ov001_020631e4(session->scriptResult);
        case 0:
            ReleaseSessionHandle_02062c98(session, FALSE);
            work->finish(session->finishArg);
            nextState = 10;
            func_ov001_02062cd4(session);
            func_ov001_020630e4();
            break;
        }
    }
    return nextState;
}
