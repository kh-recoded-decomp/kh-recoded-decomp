#include "nitro/types.h"

extern BOOL HasSessionContext(void);
extern s32 GetFieldSessionState(void);
extern void RequestSceneEvent(u32 index, u32 value, u32 flags);
extern void *gStageManager;

BOOL RequestSceneEventWhenSessionState6(u32 id, u32 value)
{
    s32 sessionMode;

    if (HasSessionContext()) {
        sessionMode = GetFieldSessionState();
    } else {
        sessionMode = 0;
    }
    if (sessionMode != 6) {
        return FALSE;
    }
    if (gStageManager != NULL) {
        if (id != 0) {
            RequestSceneEvent(id - 1, value, 0);
        }
        return TRUE;
    }
    return FALSE;
}
