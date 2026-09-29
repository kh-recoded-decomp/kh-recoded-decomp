#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;
typedef struct LayoutElement LayoutElement;

extern LayoutElement *func_ov027_020b90a4(ResourceContainer *container, s32 elementId);
extern void func_ov027_020b9580(ResourceContainer *container, LayoutElement *element, BOOL visible);

void SetLayoutElementVisible_020d0e4c(ResourceContainer *layout, s32 elementId, BOOL visible)
{
    func_ov027_020b9580(layout, func_ov027_020b90a4(layout, elementId), visible);
}
