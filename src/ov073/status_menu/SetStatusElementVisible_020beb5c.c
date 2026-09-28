#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern ResourceContainer *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(ResourceContainer *container, int id);
extern void func_ov027_020b9580(ResourceContainer *container, void *element, BOOL visible);

void SetStatusElementVisible_020beb5c(int elementId, BOOL visible)
{
    ResourceContainer *container = func_ov039_020bc1cc();

    func_ov027_020b9580(container, func_ov027_020b90a4(container, elementId), visible);
}
