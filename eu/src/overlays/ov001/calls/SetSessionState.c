#include "nitro/types.h"

typedef s32 (*StateInitFunc)(void *params);
typedef void (*StateUpdateFunc)(void *params);

typedef struct StateParams {
    u8 mode;
    s8 ctxMode;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} StateParams;

typedef struct StateMachine {
    s32 handle;
    s32 overlayId;
    s8 state;
    s8 prevState;
    u8 pad_0A[2];
    StateInitFunc init;
    u8 pad_10[0x14];
    StateUpdateFunc update;
    u8 pad_28[0x7c];
    StateParams params;
} StateMachine;

typedef struct SessionFlags {
    u32 unk_0 : 3;
    u32 bit3 : 1;
    u32 bit4 : 1;
    u32 unk_5 : 27;
} SessionFlags;

typedef struct Session {
    u8 pad_0000[0xc];
    s32 overlayId;
    u8 pad_0010[0x1f8];
    s16 unk_208;
    s16 unk_20A;
    u8 pad_020c[8];
    SessionFlags flags;
    u8 pad_0218[0x259e];
    u8 optionEnabled : 1;
    u8 optionRest : 7;
    u8 pad_27b7[0x49];
    StateMachine machine;
} Session;

extern Session *data_ov001_020a0480;
extern s32 gSessionStateOverlayIds[];
extern u8 sOv001_BaEfShBin_0209e700[];
extern u8 OVERLAY_21_ID[];

extern int DeferredDraw_Release();
extern void LoadSharedModel(void *resource);
extern BOOL IsSessionFlagSet(u32 value);
extern void ClearSessionPackedBit(u32 value);
extern s8 func_ov001_02068084(void);
extern void ShutdownSessionOverlays(void);
extern void func_02029f8c(int processor, int overlayId);
extern void func_02029fac(int processor, int overlayId);
extern void InitScriptHandlerTable(void);
extern void ClearStageTablesIfActive(void);
extern void func_ov001_02062ac0(void);
extern void ResetSessionPanel(void);
extern void func_ov001_02062bf4(void);
extern void func_ov001_02062ad8(void);
extern void ActivateResumeModeHandlers(void);
extern void func_ov001_02062b84(void);
extern void func_ov001_02062af0(void);
extern void func_ov001_02062c0c(void);
extern void ResumeSessionPanel(void);
extern void func_ov001_02062bdc(void);
extern void ActivateSubModeHandlers(void);
extern void func_ov001_02062c4c(void);

s32 SetSessionState(s32 newState, s32 mode) {
    Session *session = data_ov001_020a0480;
    StateMachine *machine = &session->machine;
    s32 overlayId;

    DeferredDraw_Release();
    LoadSharedModel(sOv001_BaEfShBin_0209e700);

    if (session->flags.bit3) {
        if (IsSessionFlagSet(0x3635)) {
            machine->params.mode = 3;
            ClearSessionPackedBit(0x3635);
        }
    } else if (session->optionEnabled && !session->flags.bit4) {
        machine->params.mode = 1;
    } else {
        machine->params.mode = mode;
    }

    machine->params.ctxMode = func_ov001_02068084();
    machine->params.unk_02 = session->unk_208;
    machine->params.unk_04 = session->unk_20A;
    machine->params.unk_06 = 0;

    if (machine->state == newState) {
        machine->prevState = machine->state;
    } else {
        if (machine->state >= 0) {
            ShutdownSessionOverlays();
        }
        if (newState != 1) {
            if (session->overlayId == -1) {
                session->overlayId = (s32)OVERLAY_21_ID;
                func_02029f8c(0, (s32)OVERLAY_21_ID);
                InitScriptHandlerTable();
            }
        } else {
            if (session->overlayId != -1) {
                func_02029fac(0, session->overlayId);
                session->overlayId = -1;
            }
            ClearStageTablesIfActive();
        }

        overlayId = gSessionStateOverlayIds[newState];
        if (overlayId != -1) {
            machine->overlayId = overlayId;
            func_02029f8c(0, overlayId);
        }

        switch (newState) {
        case 0:
            func_ov001_02062ac0();
            break;
        case 1:
            ResetSessionPanel();
            break;
        case 3:
            func_ov001_02062bf4();
            break;
        case 4:
            func_ov001_02062ad8();
            break;
        case 5:
            ActivateResumeModeHandlers();
            break;
        case 6:
            func_ov001_02062b84();
            break;
        case 7:
            func_ov001_02062af0();
            break;
        case 8:
            func_ov001_02062c0c();
            break;
        case 9:
            ResumeSessionPanel();
            break;
        case 10:
            func_ov001_02062bdc();
            break;
        case 11:
            ActivateSubModeHandlers();
            break;
        case 12:
            func_ov001_02062c4c();
            break;
        }

        machine->prevState = machine->state;
        machine->state = newState;
    }

    if (machine->handle == -1) {
        machine->handle = machine->init(&machine->params);
    } else if (machine->update != NULL) {
        machine->update(&machine->params);
    }
    return 1;
}
