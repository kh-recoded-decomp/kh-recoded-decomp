#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x828];
    s8 runFlags;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
    u8 pad_2739[0x2744 - 0x2739];
    s8 pendingCount;
    u8 pad_2745[0x27b6 - 0x2745];
    u8 statusFlags;
} Session;

extern Session *data_ov001_020a0460;
extern int func_ov000_02062c64(void);

#ifndef SESSION_SCRIPT_RUN_FLAG
#define SESSION_SCRIPT_RUN_FLAG 0x80
#endif

BOOL TryRaiseSessionScriptFlags_02063694(void) {
    Session *session = data_ov001_020a0460;
    SessionScript *script = &session->script;
    if (session->pendingCount > 0) {
        return FALSE;
    }
    if (func_ov000_02062c64() == 0) {
        return FALSE;
    }
    script->runFlags |= SESSION_SCRIPT_RUN_FLAG;
    session->statusFlags |= 0x10;
    return TRUE;
}
