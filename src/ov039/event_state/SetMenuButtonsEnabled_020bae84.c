#include "nitro/types.h"

extern int data_ov039_020bea00;
extern void SetFlagBit0_020b85a8(unsigned char *flags, int value);
extern void func_ov027_020b85c4(int button);
extern void SetWidgetRootDpadEnabled_020b9874(int root, BOOL enabled);
extern void SetWidgetRootTouchEnabled_020b984c(int root, BOOL enabled);

void SetMenuButtonsEnabled_020bae84(BOOL enable)
{
    int base = data_ov039_020bea00;
    BOOL first = enable && *(int *)(base + 0xca18) != 0;
    BOOL second = enable && *(int *)(base + 0xca1c) != 0;

    SetFlagBit0_020b85a8((unsigned char *)(base + 0xc8f8), first);
    SetFlagBit0_020b85a8((unsigned char *)(base + 0xc944), second);
    func_ov027_020b85c4(base + 0xc8f8);
    func_ov027_020b85c4(base + 0xc944);
    SetWidgetRootDpadEnabled_020b9874(base + 0x647c, second);
    SetWidgetRootTouchEnabled_020b984c(base + 0x647c, second);
}
