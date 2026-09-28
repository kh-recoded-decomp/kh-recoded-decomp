#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;
struct PMSleepCallbackInfo {
    void (*callback)(void *arg);
    void *arg;
    u32 pad_08;
    PMSleepCallbackInfo *next;
};

void PMi_ExecuteList_02010aac(PMSleepCallbackInfo *listp)
{
    while (listp != NULL) {
        listp->callback(listp->arg);
        listp = listp->next;
    }
}
