#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct CallbackEntry {
    void (*callback)(void);
    NNSFndLink link;
    u8 pad_0C[4];
} CallbackEntry;

typedef struct SessionState {
    void *session;
    NNSFndList callbackList;
} SessionState;

extern SessionState g_sessionState_020a0488;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);

void RegisterSessionCallback_0206c704(void (*callback)(void))
{
    CallbackEntry *entry;

    entry = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(CallbackEntry));
    entry->callback = callback;
    AppendIntrusiveListObject_020128d0(&g_sessionState_020a0488.callbackList, entry);
}
