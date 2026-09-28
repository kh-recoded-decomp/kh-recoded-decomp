#include "nitro/types.h"

extern void func_01ff86fc(unsigned int data, void *dst, unsigned int size);

void ClearBuffer2048_02078f00(void *dst) {
    func_01ff86fc(0, dst, 0x800);
}
