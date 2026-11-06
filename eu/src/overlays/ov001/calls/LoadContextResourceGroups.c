#include "nitro/types.h"

typedef struct ResourceContext ResourceContext;

extern ResourceContext *gCounterHudWork;
extern void LoadResourceGroups(ResourceContext *context, u32 mask);

void LoadContextResourceGroups(u32 mask)
{
    LoadResourceGroups(gCounterHudWork, mask);
}
