#include "nitro/types.h"

typedef struct MenuStateCallbacks {
    void (*enter)(void);
    void (*update)(void);
    void (*leave)(void);
} MenuStateCallbacks;

typedef struct MenuContext {
    s8 state;
    s8 result;
    u8 pad_02[0x56c - 2];
    u8 listA[0x69e8 - 0x56c];
    u8 listB[4];
} MenuContext;

extern MenuContext *g_context_0206c464;
extern MenuStateCallbacks gMenuStateTable[];
extern void func_ov002_020649b0(void);
extern void func_ov002_02064d54(void);
extern void NNS_FndInitListWithOffset0_0204f11c(void *list);
extern u32 func_ov002_0206655c(void);

int UpdateMenuContext_02064328(void)
{
    gMenuStateTable[g_context_0206c464->state].update();
    func_ov002_020649b0();
    func_ov002_02064d54();
    NNS_FndInitListWithOffset0_0204f11c(g_context_0206c464->listA);
    NNS_FndInitListWithOffset0_0204f11c(g_context_0206c464->listB);
    if (func_ov002_0206655c()) {
        return g_context_0206c464->result;
    }
    return 0;
}
