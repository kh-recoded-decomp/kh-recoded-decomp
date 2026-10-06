#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x52c];
    u32 unk_52c;
} Manager;

extern u32 data_ov035_020bc4e0;

void func_ov041_020bcd78(void) {
    Manager *manager = *(Manager **)(data_ov035_020bc4e0 + 0xb8);
    manager->unk_52c = 0;
}
