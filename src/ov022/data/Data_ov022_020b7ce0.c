#include "nitro/types.h"

extern void CmdPrepareStream_020a79e8(void);
extern void MsgQueue_GetHeap_020a79c8(void);
extern void ScriptCmd_EnterPhase_020a793c(void);
extern void ScriptCmd_EnterPhase_020a79b8(void);
extern void func_ov022_020a794c(void);
extern void func_ov022_020a7958(void);
extern void func_ov022_020a7990(void);
extern void thumbStep_020a79d4(void);

void (*data_ov022_020b7ce0[12])(void) = {
    func_ov022_020a794c,
    NULL,
    ScriptCmd_EnterPhase_020a79b8,
    NULL,
    ScriptCmd_EnterPhase_020a793c,
    NULL,
    func_ov022_020a7958,
    func_ov022_020a7990,
    MsgQueue_GetHeap_020a79c8,
    thumbStep_020a79d4,
    CmdPrepareStream_020a79e8,
    NULL,
};
