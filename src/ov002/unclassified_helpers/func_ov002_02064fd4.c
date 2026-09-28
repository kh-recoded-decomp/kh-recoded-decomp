#include "nitro/types.h"

extern u32 g_context_0206c464;
extern void func_ov002_020648c0(void);
extern void func_ov002_020643a0(void);

void func_ov002_02064fd4(void) {
    func_ov002_020648c0();
    func_ov002_020643a0();
    *(u32 *)(g_context_0206c464 + 8) = 0;
}
