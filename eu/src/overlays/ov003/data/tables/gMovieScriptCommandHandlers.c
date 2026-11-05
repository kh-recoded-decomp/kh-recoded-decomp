#include "nitro/types.h"

extern void MovieScene_BeginDefaultFade(void); /* MovieScene_BeginDefaultFade */
extern void ResyncMovieSubtitleStream(void); /* ResyncMovieSubtitleStream */
extern void MovieScriptCmd_StartStream(void);
extern void MovieScriptCmd_WaitForSubtitleFrame(void);
extern void MovieScriptPoll_SubtitleFrame(void);
extern void MovieScriptCmd_RequestStop(void); /* MsgQueue_GetHeap */
extern void MovieScriptPoll_StopRequestClear(void); /* thumbStep */

void (*gMovieScriptCommandHandlers[10])(void) = {
    MovieScene_BeginDefaultFade, /* MovieScene_BeginDefaultFade */
    NULL,
    ResyncMovieSubtitleStream, /* ResyncMovieSubtitleStream */
    NULL,
    MovieScriptCmd_StartStream,
    NULL,
    MovieScriptCmd_WaitForSubtitleFrame,
    MovieScriptPoll_SubtitleFrame,
    MovieScriptCmd_RequestStop, /* MsgQueue_GetHeap */
    MovieScriptPoll_StopRequestClear, /* thumbStep */
};
