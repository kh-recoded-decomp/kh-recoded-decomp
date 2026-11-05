#include "nitro/types.h"

extern void StartSubtitlePlaybackAndReturnState6(void);
extern void MovieScriptCmd_SetCaptionText(void); /* ScriptCmd_EnterPhase */
extern void MovieScriptCmd_OpenCaptionScreen(void); /* ScriptCmd_EnterPhase */
extern void MovieScriptCmd_WaitPresentedFrame(void);
extern void MovieScriptWait_PresentedFrame(void);
extern void MovieScriptCmd_CommitCaptionText(void); /* MsgQueue_GetHeap */
extern void MovieScriptWait_CaptionTransferFlagClear(void); /* thumbStep */
extern void CmdPrepareStream_020a7a08(void); /* CmdPrepareStream */

void (*gStreamScriptCommandHandlers[12])(void) = {
    StartSubtitlePlaybackAndReturnState6,
    NULL,
    MovieScriptCmd_SetCaptionText, /* ScriptCmd_EnterPhase */
    NULL,
    MovieScriptCmd_OpenCaptionScreen, /* ScriptCmd_EnterPhase */
    NULL,
    MovieScriptCmd_WaitPresentedFrame,
    MovieScriptWait_PresentedFrame,
    MovieScriptCmd_CommitCaptionText, /* MsgQueue_GetHeap */
    MovieScriptWait_CaptionTransferFlagClear, /* thumbStep */
    CmdPrepareStream_020a7a08, /* CmdPrepareStream */
    NULL,
};
