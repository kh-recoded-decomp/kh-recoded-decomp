#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 modelGroupResource;
} RegistryHead;

extern u32 func_0202c478(u32 fileId, u32 param2, u32 param3, u32 param4);
extern int ModelGroup_Open_0203510c(void *g, void *res);
extern RegistryHead *g_recordTablePtr_0206083c;

BOOL func_020357b4(u32 param1, u32 param2, u32 param3, u32 param4) {
    RegistryHead *registry = g_recordTablePtr_0206083c;
    u32 result = func_0202c478(param2, 1, param3, param4);
    ModelGroup_Open_0203510c(registry, (void *)result);
    registry->modelGroupResource = result;
    return TRUE;
}
