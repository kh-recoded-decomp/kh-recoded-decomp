#include "nitro/types.h"

extern void func_0202a1c4(void *ptr);
extern void func_ov015_0207634c(void);
extern void *data_ov015_020812e0;

void ReleaseWorkBuffer_020752f4(void) {
    func_ov015_0207634c();
    if (data_ov015_020812e0 == 0) {
        return;
    }
    func_0202a1c4(data_ov015_020812e0);
    data_ov015_020812e0 = 0;
}
