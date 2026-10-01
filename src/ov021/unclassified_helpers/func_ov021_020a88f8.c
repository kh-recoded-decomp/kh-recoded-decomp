#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct {
    BOOL initialized;
    NNSFndList groupList;
    s32 groupCount;
    u16 nextGroupId;
} EntryRegistry;

extern BOOL g_registryInitialized_020b5608;
extern EntryRegistry g_entryRegistry_020b5608;
extern void func_0201288c(NNSFndList *list, u16 offset);
extern void RegisterSessionCallback_0206c704(void (*callback)(void));
extern void func_ov021_020a8f74(void);

void func_ov021_020a88f8(void)
{
    EntryRegistry *registry = &g_entryRegistry_020b5608;

    if (g_registryInitialized_020b5608 == FALSE) {
        registry->initialized = TRUE;
        registry->groupCount = 0;
        registry->nextGroupId = 0;
        func_0201288c(&registry->groupList, 0x10);
        RegisterSessionCallback_0206c704(func_ov021_020a8f74);
    }
}
