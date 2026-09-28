#include "nitro/types.h"

extern void func_ov015_02079cd4(void *ptr);
extern void func_ov027_020b8c58(void *ptr);
extern void func_ov027_020ba294(void *ptr);
extern u8 *data_ov015_020812e0;

void func_ov015_0207634c(void) {
    func_ov027_020b8c58(data_ov015_020812e0 + 0x160);
    func_ov027_020ba294(data_ov015_020812e0 + 0x65e0);
    func_ov015_02079cd4(data_ov015_020812e0 + 0x65ec);
    func_ov015_02079cd4(data_ov015_020812e0 + 0x65f0);
    func_ov015_02079cd4(data_ov015_020812e0 + 0x65f4);
}
