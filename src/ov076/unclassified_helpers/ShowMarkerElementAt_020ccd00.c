#include "nitro/types.h"

extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void func_ov027_020b91c8(void *container, void *element, const s32 *position, int mode);

void ShowMarkerElementAt_020ccd00(void *container, const s32 *position)
{
    void *marker = func_ov027_020b90a4(container, 0x2a);

    func_ov027_020b9580(container, marker, position != NULL);
    if (position != NULL) {
        func_ov027_020b91c8(container, marker, position, 0);
    }
}
