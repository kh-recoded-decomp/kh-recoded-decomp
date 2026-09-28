#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(void *object);
extern u32 func_ov001_0207f20c(int parentContext, u32 param2);

void ReleaseChildResourceAndForward_020a0910(int parentContext, u32 param2) {
    int child = *(int *)(parentContext + 8);
    if (*(int *)(child + 0x84) != 0) {
        *(int *)(child + 0x84) = 0;
        ReleaseResourceAndDetach_0202eee8((void *)(child + 0x88));
    }
    func_ov001_0207f20c(parentContext, param2);
}
