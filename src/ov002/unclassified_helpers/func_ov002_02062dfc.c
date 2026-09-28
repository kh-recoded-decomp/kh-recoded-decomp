#include "nitro/types.h"

extern s32 func_ov014_0206cf38(void);
extern void func_ov002_02062cb8(s32 value);

void func_ov002_02062dfc(void) {
    s32 status = func_ov014_0206cf38();
    if (status != 1) {
        return;
    }
    func_ov002_02062cb8(0);
}
