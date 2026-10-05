#include "nitro/types.h"

typedef struct ResourceContext ResourceContext;

extern ResourceContext *data_ov001_020a04cc;
extern void LoadResourceGroups_0207c770(ResourceContext *context, u32 mask);

void LoadContextResourceGroups_0207d120(u32 mask)
{
    LoadResourceGroups_0207c770(data_ov001_020a04cc, mask);
}
