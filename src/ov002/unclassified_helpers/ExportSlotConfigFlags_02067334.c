#include "nitro/types.h"

typedef struct ContextSlot {
    u8 pad_00[0x38];
    u32 unk_38_b0 : 17;
    u32 configFlag : 1;
    u32 unk_38_b18 : 14;
    u8 pad_3C[0x10];
} ContextSlot;

typedef struct ContextConfig {
    ContextSlot slots[90];
    u8 pad_1AB8[0x10];
    u32 slotCount : 7;
    u32 unk_1AC8_b7 : 25;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);
extern void func_01ff8830(void *dst, int value, u32 size);

void ExportSlotConfigFlags_02067334(u8 *flags) {
    u32 slotIndex;
    ContextConfig *config;

    config = func_ov002_02066fe0();
    slotIndex = 0;

    func_01ff8830(flags, slotIndex, sizeof(config->slots) / sizeof(config->slots[0]));
    for (; slotIndex < config->slotCount; slotIndex++) {
        flags[slotIndex] = config->slots[slotIndex].configFlag;
    }
}
