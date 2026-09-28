#include "nitro/types.h"

extern BOOL func_02036164(u8 typeId);
extern void func_ov001_02087258(int self, BOOL flag);

void ApplyTypeCapabilityFlag_020a3138(int self) {
    BOOL flag = func_02036164(*(u8 *)(self + 0x32));
    func_ov001_02087258(self, flag);
}
