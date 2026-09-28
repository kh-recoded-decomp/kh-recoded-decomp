#include "nitro/types.h"

extern u32 g_context_0206c464;
extern void func_ov027_020ba294(u32 target);
extern void func_ov027_020b7dfc(u32 target);
extern void func_ov027_020b8c58(u32 target);
extern int ZeroHalfThenFree_0202cd78(void *ptr);
extern void func_0202a1c4(u32 target);

void ReleaseContextResources_020642b8(void) {
    func_ov027_020ba294(g_context_0206c464 + 0xce64);
    func_ov027_020b7dfc(g_context_0206c464 + 0x520);
    func_ov027_020b7dfc(g_context_0206c464 + 0x4d4);
    func_ov027_020b8c58(g_context_0206c464 + 0x69e8);
    func_ov027_020b8c58(g_context_0206c464 + 0x56c);
    ZeroHalfThenFree_0202cd78((void *)*(u32 *)(g_context_0206c464 + 0x24));
    func_0202a1c4(g_context_0206c464);
}
