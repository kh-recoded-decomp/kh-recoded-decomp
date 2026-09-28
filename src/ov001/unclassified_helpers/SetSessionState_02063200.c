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

extern Session *data_ov001_020a0460;
extern s32 data_ov001_0209e64c[];
extern u8 data_ov001_0209e6e0[];
extern u8 SDK_OVERLAY_ov021_ID_00000015[];

extern int DeferredDraw_Release_02036b20();
extern void func_02036ac0(void *resource);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_020645e8(u32 value);
extern s8 GetCtxModeByte_02068084(void);
extern void func_ov001_02062a54(void);
extern void func_02029f78(int processor, int overlayId);
extern void func_02029f98(int processor, int overlayId);
extern void func_ov021_020b4884(void);
extern void func_ov001_020876cc(void);
extern void func_ov001_02062ac0(void);
extern void func_ov001_02062b9c(void);
extern void func_ov001_02062bf4(void);
extern void func_ov001_02062ad8(void);
extern void func_ov001_02062b08(void);
extern void func_ov001_02062b84(void);
extern void func_ov001_02062af0(void);
extern void func_ov001_02062c0c(void);
extern void func_ov001_02062c24(void);
extern void func_ov000_02062bdc(void);
extern void func_ov001_02062b48(void);
extern void func_ov001_02062c4c(void);

s32 SetSessionState_02063200(s32 newState, s32 mode) {
    Session *session = data_ov001_020a0460;
    StateMachine *machine = &session->machine;
    s32 overlayId;

    DeferredDraw_Release_02036b20();
    func_02036ac0(data_ov001_0209e6e0);

    if (session->flags.bit3) {
        if (func_ov001_020645c8(0x3635)) {
            machine->params.mode = 3;
            func_ov001_020645e8(0x3635);
        }
    } else if (session->optionEnabled && !session->flags.bit4) {
        machine->params.mode = 1;
    } else {
        machine->params.mode = mode;
    }

    machine->params.ctxMode = GetCtxModeByte_02068084();
    machine->params.unk_02 = session->unk_208;
    machine->params.unk_04 = session->unk_20A;
    machine->params.unk_06 = 0;

    if (machine->state == newState) {
        machine->prevState = machine->state;
    } else {
        if (machine->state >= 0) {
            func_ov001_02062a54();
        }
        if (newState != 1) {
            if (session->overlayId == -1) {
                session->overlayId = (s32)SDK_OVERLAY_ov021_ID_00000015;
                func_02029f78(0, (s32)SDK_OVERLAY_ov021_ID_00000015);
                func_ov021_020b4884();
            }
        } else {
            if (session->overlayId != -1) {
                func_02029f98(0, session->overlayId);
                session->overlayId = -1;
            }
            func_ov001_020876cc();
        }

        overlayId = data_ov001_0209e64c[newState];
        if (overlayId != -1) {
            machine->overlayId = overlayId;
            func_02029f78(0, overlayId);
        }

        switch (newState) {
        case 0:
            func_ov001_02062ac0();
            break;
        case 1:
            func_ov001_02062b9c();
            break;
        case 3:
            func_ov001_02062bf4();
            break;
        case 4:
            func_ov001_02062ad8();
            break;
        case 5:
            func_ov001_02062b08();
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
            func_ov001_02062c24();
            break;
        case 10:
            func_ov000_02062bdc();
            break;
        case 11:
            func_ov001_02062b48();
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
