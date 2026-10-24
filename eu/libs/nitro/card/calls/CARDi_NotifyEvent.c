#pragma ipa file

#include "libs/nitro/os/os_interrupt_state.h"

typedef unsigned long u32;
typedef u32 CARDEvent;
typedef unsigned long OSIntrMode;

typedef void (*CARDHookFunction)(void *userData, CARDEvent event,
                                 void *argument);

typedef struct CARDHookContext {
    struct CARDHookContext *next;
    void *userData;
    CARDHookFunction callback;
} CARDHookContext;

CARDHookContext *CARDiHookChain;
extern OSIntrMode OS_DisableInterrupts(void);


void CARDi_NotifyEvent(CARDEvent event, void *argument)
{
    OSIntrMode previousMode = OS_DisableInterrupts();
    CARDHookContext **link = &CARDiHookChain;

    while (*link) {
        CARDHookContext *hook = *link;

        if (hook->callback) {
            (*hook->callback)(hook->userData, event, argument);
        }
        if (*link == hook) {
            link = &(*link)->next;
        }
    }

    (void)OS_RestoreInterrupts(previousMode);
}