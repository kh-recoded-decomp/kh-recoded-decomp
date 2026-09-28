#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct CallbackEntry {
    void (*callback)(void);
} CallbackEntry;

typedef struct SessionState {
    void *session;
    NNSFndList callbackList;
} SessionState;

extern SessionState g_sessionState_020a0488;
extern void *NNS_FndGetNextListObject_02012a38(NNSFndList *list, void *object);

BOOL RunSessionCallbacks_0206c684(void)
{
    SessionState *state;
    CallbackEntry *entry;
    CallbackEntry *next;

    state = &g_sessionState_020a0488;
    entry = NNS_FndGetNextListObject_02012a38(&g_sessionState_020a0488.callbackList, NULL);
    while (entry != NULL) {
        next = NNS_FndGetNextListObject_02012a38(&state->callbackList, entry);
        entry->callback();
        entry = next;
    }
    return FALSE;
}
