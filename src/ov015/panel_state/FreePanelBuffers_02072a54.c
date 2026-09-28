#include "nitro/types.h"

extern void func_0202a1c4(void *ptr);
extern u8 *data_ov015_0207e964;

void FreePanelBuffers_02072a54(void) {
    int i;

    func_0202a1c4(*(void **)(data_ov015_0207e964 + 0x94));
    i = 0;
    do {
        func_0202a1c4(*(void **)(data_ov015_0207e964 + i * 4 + 0x98));
        i = i + 1;
    } while (i < 4);
    func_0202a1c4(data_ov015_0207e964);
}
