#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x60];
    void *listHead;
} OverlayObject;

extern void *func_ov017_020a50d8();
extern void func_ov017_020a4100(OverlayObject *obj);

void RefreshListHeadAndDispatch_020a423c(OverlayObject *obj)
{
    if (obj->listHead != 0) {
        obj->listHead = func_ov017_020a50d8();
        func_ov017_020a4100(obj);
    }
}
