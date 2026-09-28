#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 bit6 : 1;
    u32 unk_7 : 5;
    u32 bit12 : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct Session {
    u8 pad_000[0x20];
    u32 stateFlags;
    u8 pad_024[0x1F0];
    SessionFlags flags;
} Session;

typedef struct FieldObject {
    u8 pad_00[0x58];
    u8 isRunning;
    s8 configFlags;
    u8 pad_5A[0xA];
    char eventLabel[8];
    char scriptName[8];
} FieldObject;

extern Session *data_ov001_020a0460;
extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern BOOL IsFirstEntryFlagSet_0206e584(void);
extern u32 func_ov001_02063620(void);
extern BOOL func_ov001_02064490(void);
extern BOOL TryBeginSessionEvent_02063694(void);
extern void StartSessionScript_020635b0(char *eventLabel, char *scriptName);
extern void SetActorsEnabled_0206e444(BOOL enabled);
extern void SetSessionFinishCallback_02063678(void (*onFinish)(FieldObject *object), FieldObject *object);
extern void func_ov001_02080e5c(FieldObject *object);

BOOL FieldObject_TryStartEvent_02081014(FieldObject *object)
{
    if (object->isRunning) {
        return FALSE;
    }
    if (object->scriptName[0] == 0) {
        return FALSE;
    }
    if (!(object->configFlags & 0x80) && FieldObject_GetSavedValue_0207f9a8(object) != 0) {
        return FALSE;
    }
    if (IsFirstEntryFlagSet_0206e584()) {
        return FALSE;
    }
    if (func_ov001_02063620() != 0 || (data_ov001_020a0460->stateFlags & 0x10) ||
        data_ov001_020a0460->flags.bit12 || data_ov001_020a0460->flags.bit6 ||
        func_ov001_02064490()) {
        return FALSE;
    }
    if (TryBeginSessionEvent_02063694()) {
        StartSessionScript_020635b0(object->eventLabel[0] ? object->eventLabel : NULL, object->scriptName);
        SetActorsEnabled_0206e444(TRUE);
        SetSessionFinishCallback_02063678(func_ov001_02080e5c, object);
        object->isRunning = TRUE;
    }
    return FALSE;
}
