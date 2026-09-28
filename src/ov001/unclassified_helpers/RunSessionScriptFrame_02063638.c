#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x1cc];
    s32 status;
    u8 pad_1d0[0x828 - 0x1d0];
    s8 runFlags;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
} Session;

extern Session *data_ov001_020a0460;
extern int ScriptVm_RunFrame_02025b18(SessionScript *vm);
extern BOOL func_020258f8(SessionScript *vm);

s32 RunSessionScriptFrame_02063638(void) {
    SessionScript *script = &data_ov001_020a0460->script;
    script->runFlags |= 1;
    if (ScriptVm_RunFrame_02025b18(script) == 0) {
        func_020258f8(script);
        script->runFlags = 0;
        return script->status;
    }
    return -1;
}
