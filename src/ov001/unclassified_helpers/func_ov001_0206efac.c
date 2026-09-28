#include "nitro/types.h"

extern void func_01ff878c(u32 dest, u32 src, u32 size);
extern void func_020033e0(void);
extern void func_02007250(u32 dest, u32 value, u32 size);
extern void func_02007b70(u32 dest, u32 value, u32 size);
extern s32 func_02014d38(u32 resourceManager, s32 *outPayload);
extern s32 func_ov001_02073598(void);
extern void func_ov001_0206ed8c(u16 flags);

void func_ov001_0206efac(s32 context, u32 resourceManager, u32 unused1, u32 unused2)
{
    s32 slotIndex;
    s32 payload;
    u32 unusedCopy;

    *(u32 *)(context + 0x480) &= 0xffff7fff;
    unusedCopy = unused2;
    func_02014d38(resourceManager, &payload);
    func_01ff878c(*(u32 *)(payload + 0x14), *(u32 *)(context + 0x460), 0x80);
    func_01ff878c(*(u32 *)(payload + 0x14) + 0x80, *(u32 *)(context + 0x468), 0x80);
    func_01ff878c(*(u32 *)(payload + 0x14) + 0x100, *(u32 *)(context + 0x464), 0x80);
    func_020033e0();
    func_02007b70(*(u32 *)(payload + 0x14) + 0x180, 0x5900, *(u32 *)(payload + 0x10) - 0x180);
    slotIndex = func_ov001_02073598();
    func_02007250(*(u32 *)(context + 0x470) + slotIndex * 0x20, 0x100, 0x20);
    func_ov001_0206ed8c(*(u16 *)(context + 0x476));
}
