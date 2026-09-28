#include "nitro/types.h"
#include "nitro/os_types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;
struct PMSleepCallbackInfo {
    void (*callback)(void *arg);
    void *arg;
    int priority;
    PMSleepCallbackInfo *next;
};

extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);

void PMi_InsertList_02010a1c(PMSleepCallbackInfo **listp, PMSleepCallbackInfo *info, int priority, int method)
{
    OSIntrMode intr;
    PMSleepCallbackInfo *p;
    PMSleepCallbackInfo *pPrev;

    if (!listp) {
        return;
    }

    info->priority = priority;

    intr = OS_DisableInterrupts_02004938();
    p = *listp;
    pPrev = NULL;

    while (p) {
        if (method == 0 && p->priority > priority) {
            break;
        }
        if (method == 1 && p->priority >= priority) {
            break;
        }
        pPrev = p;
        p = p->next;
    }

    if (p) {
        info->next = p;
    } else {
        info->next = NULL;
    }

    if (pPrev) {
        pPrev->next = info;
    } else {
        *listp = info;
    }

    (void)OS_RestoreInterrupts_0200494c(intr);
}
