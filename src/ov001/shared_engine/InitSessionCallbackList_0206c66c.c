#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct SessionState {
    void *session;
    NNSFndList callbackList;
} SessionState;

extern SessionState g_sessionState_020a0488;
extern void *func_0201288c(NNSFndList *list, u16 offset);
extern BOOL RunSessionCallbacks_0206c684(void);

void *InitSessionCallbackList_0206c66c(void)
{
    func_0201288c(&g_sessionState_020a0488.callbackList, 4);
    return RunSessionCallbacks_0206c684;
}
