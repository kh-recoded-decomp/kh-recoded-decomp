#include "nitro/types.h"

typedef struct TargetData {
    u8 pad_00[0x7d];
    u8 category;
} TargetData;

typedef struct TargetObject {
    u8 pad_00[0x08];
    TargetData *data;
} TargetObject;

typedef struct TargetInfo {
    u8 kind;
    u8 pad_01[0x03];
    TargetObject *object;
    u8 pad_08[0x0c];
} TargetInfo;

typedef struct FieldPlayer FieldPlayer;

typedef int (*GetStateFunc)(FieldPlayer *player);

struct FieldPlayer {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x4c];
    GetStateFunc getState;
};

extern BOOL func_ov052_020cfb58(FieldPlayer *player);
extern BOOL func_ov001_020645c8(u32 flag);
extern BOOL func_ov001_0206c328(TargetInfo *target);
extern u32 func_ov001_0207f8f4(TargetObject *object);
extern void func_ov007_020a1b08(TargetObject *object, s32 *outEventId, u32 *outEventArg);
extern void func_ov001_02078360(BOOL a, BOOL b);
extern void func_ov036_020be0f8(TargetObject *object);
extern BOOL func_ov036_020be0c4(FieldPlayer *player, s32 eventId, u32 eventArg);
extern BOOL func_ov001_0207fa2c(TargetObject *object);
extern int func_ov001_020644b0(void);
extern int func_ov001_0206dc38(void);
extern void func_ov001_02077c98(BOOL show);
extern BOOL func_ov001_02064280(void);
extern BOOL func_ov001_020642a0(void);
extern BOOL func_ov001_0206e31c(void);
extern BOOL func_ov010_020a1958(void);
extern int func_ov001_02064784(void);
extern u32 func_ov001_02077bcc(void);
extern void func_ov001_02072064(int command);

static inline int FieldPlayer_GetState(FieldPlayer *player)
{
    if (player->getState != NULL) {
        return player->getState(player);
    }
    return player->state;
}

void UpdateActionCommand_0206d0ac(FieldPlayer *player)
{
    BOOL useDefaultCommand = FALSE;
    BOOL clearCommand = FALSE;
    BOOL showCommand = TRUE;
    int command = -1;
    u8 kind = 0;
    BOOL atCheckpoint;
    TargetInfo target;
    s32 eventId;
    u32 eventArg;

    if (func_ov052_020cfb58(player) && !func_ov001_020645c8(0x3520)) {
        useDefaultCommand = TRUE;
    }
    if (func_ov001_0206c328(&target)) {
        kind = target.kind;
    }

    switch (kind) {
    case 2: {
        TargetObject *object = target.object;
        switch (func_ov001_0207f8f4(object)) {
        case 0:
            if (useDefaultCommand) {
                command = 0;
            }
            break;
        case 1:
            atCheckpoint = TRUE;
            command = 1;
            if (object->data->category == 5) {
                func_ov007_020a1b08(object, &eventId, &eventArg);
                command = 6;
                func_ov001_02078360(TRUE, TRUE);
                func_ov036_020be0f8(object);
                if (func_ov036_020be0c4(player, eventId, eventArg)) {
                    command = 9;
                }
                showCommand = FALSE;
                break;
            }
            if (func_ov001_0207fa2c(object)) {
                break;
            }
            if (func_ov001_020644b0() != 900) {
                atCheckpoint = FALSE;
            }
            if (atCheckpoint) {
                break;
            }
            clearCommand = TRUE;
            break;
        case 2:
            command = 2;
            if (!func_ov001_0207fa2c(object)) {
                clearCommand = TRUE;
            }
            break;
        }
        break;
    }
    case 4:
        command = 8;
        break;
    default:
        if (useDefaultCommand) {
            command = 0;
        } else if (func_ov001_0206dc38() > 1) {
            command = 7;
        } else {
            command = 1;
            clearCommand = TRUE;
        }
        break;
    }

    func_ov001_02077c98(showCommand);
    if (func_ov001_02064280() && !func_ov001_020642a0()) {
        command = 3;
        clearCommand = FALSE;
    }
    if (func_ov001_0206e31c() && func_ov010_020a1958()) {
        command = 11;
    }
    if (command == 0 && func_ov001_020645c8(0x3533)) {
        clearCommand = TRUE;
    }
    if (FieldPlayer_GetState(player) == 4 || FieldPlayer_GetState(player) == 2) {
        clearCommand = TRUE;
    }
    func_ov001_02072064(command);
    if (func_ov001_02064784() == 2 && func_ov001_020645c8(0x3718) && func_ov001_02077bcc() == 13) {
        clearCommand = TRUE;
    }
    if (clearCommand) {
        func_ov001_02072064(-1);
    }
}
