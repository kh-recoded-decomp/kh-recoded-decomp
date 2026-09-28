#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern void func_ov021_020aafac();
extern void func_ov021_020ade38();

void func_ov021_020adfb8(int self)
{
    func_ov021_020ade38();
    func_ov021_020aafac(*(u32 *)(self + 0x84));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(u32 *)(self + 0x84));
}
