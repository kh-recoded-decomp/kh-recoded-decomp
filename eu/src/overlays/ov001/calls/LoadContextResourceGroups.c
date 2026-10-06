#include "nitro/types.h"

typedef struct ResourceContext ResourceContext;

extern ResourceContext *data_ov001_020a04ec;
extern void LoadResourceGroups(ResourceContext *context, u32 mask);

void LoadContextResourceGroups(u32 mask)
{
    LoadResourceGroups(data_ov001_020a04ec, mask);
}
