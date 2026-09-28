#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *field48;
} OverlayObject;

extern void ReleaseResourceAndDetach_0202eee8();
extern void func_0202a1c4(void *ptr);

void ReleaseField48_020a5438(OverlayObject *obj)
{
    if (obj->field48 != 0) {
        ReleaseResourceAndDetach_0202eee8();
        func_0202a1c4(obj->field48);
        obj->field48 = 0;
    }
}
