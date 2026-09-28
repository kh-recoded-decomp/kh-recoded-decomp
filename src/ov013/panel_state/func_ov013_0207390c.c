#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void func_02029e7c(int value);
extern void func_ov002_02066504(int mode, int value);
extern void func_ov013_0206caa4(void);
extern void func_ov013_0206e574(void);

/* Resets the panel cycle and advances the day. */
void func_ov013_0207390c(void) {
    *(int *)(data_ov013_02074ce0 + 0x2bc) = 0;
    func_02029e7c(0xfffffff0);
    func_ov002_02066504(1, 0x6000);
    func_ov013_0206caa4();
    func_ov013_0206e574();
}
