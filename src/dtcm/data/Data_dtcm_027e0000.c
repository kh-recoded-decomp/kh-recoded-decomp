#include "nitro/types.h"

extern void OSi_IrqDma0_02001cf8(void);
extern void OSi_IrqDma1_02001d08(void);
extern void OSi_IrqDma2_02001d18(void);
extern void OSi_IrqDma3_02001d28(void);
extern void OSi_IrqTimer0_02001d38(void);
extern void OSi_IrqTimer1_02001d48(void);
extern void OSi_IrqTimer2_02001d58(void);
extern void OSi_IrqTimer3_02001d68(void);
extern void func_02001c6c(void);

void (*data_027e0000[22])(void) = {
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    OSi_IrqTimer0_02001d38,
    OSi_IrqTimer1_02001d48,
    OSi_IrqTimer2_02001d58,
    OSi_IrqTimer3_02001d68,
    func_02001c6c,
    OSi_IrqDma0_02001cf8,
    OSi_IrqDma1_02001d08,
    OSi_IrqDma2_02001d18,
    OSi_IrqDma3_02001d28,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
    func_02001c6c,
};
