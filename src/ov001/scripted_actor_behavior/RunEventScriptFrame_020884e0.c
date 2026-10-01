#include "nitro/types.h"

typedef struct EventScriptState {
    u8 pad[0x140];
    u8 vm[0x1cc];
    int phase;
    u8 pad310[0x3bd4];
    u32 taskHandle;
} EventScriptState;

extern EventScriptState *data_ov001_020a04e0;
extern int ScriptVm_RunFrame_02025b18(void *vm);
extern BOOL func_020258f8(void *vm);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern BOOL func_ov001_02071898(void);
extern void func_ov001_0208bec4(void);
extern void func_ov001_02088308(void);
extern u32 func_0202a5ac(u32 handle, void (*callback)(void));

BOOL RunEventScriptFrame_020884e0(void) {
    EventScriptState *state = data_ov001_020a04e0;

    if (ScriptVm_RunFrame_02025b18(state->vm) == 0) {
        func_020258f8(state->vm);
        switch (state->phase) {
        case 0:
        case 1:
        case 2:
            WriteSessionPackedBits_0206459c(0x351f, 1, 0);
            if (func_ov001_02071898()) {
                func_ov001_0208bec4();
                func_0202a5ac(state->taskHandle, func_ov001_02088308);
                return FALSE;
            }
            break;
        }
    }
    return TRUE;
}
