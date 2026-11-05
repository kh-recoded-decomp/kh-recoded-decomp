#include "nitro/types.h"

extern void TryMarkSoundCtxActive(void); /* TryMarkSoundCtxActive */
extern void EnableOv038SoundCtx(void); /* EnableOv038SoundCtx */
extern void WaitResultsPageThenOpenFieldMenu(void);
extern void MarkSoundCtxRepeatIfReady(void); /* MarkSoundCtxRepeatIfReady */
extern void DisableOv038Sound(void); /* DisableOv038Sound */
extern void ResultsTaskStateHold(void);

void (*gResultsSoundStateHandlers[6])(void) = {
    TryMarkSoundCtxActive, /* TryMarkSoundCtxActive */
    EnableOv038SoundCtx, /* EnableOv038SoundCtx */
    WaitResultsPageThenOpenFieldMenu,
    MarkSoundCtxRepeatIfReady, /* MarkSoundCtxRepeatIfReady */
    DisableOv038Sound, /* DisableOv038Sound */
    ResultsTaskStateHold,
};
