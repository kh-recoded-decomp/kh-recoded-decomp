#include "nitro/types.h"

typedef struct {
    u8 pad_0 : 1;
    u8 doAction : 1;
    u8 doThird : 1;
    u8 pad_3to4 : 2;
    u8 doFirst : 1;
    u8 pad_6to7 : 2;
} PanelFlags98;

typedef struct {
    u8 doSecond : 1;
    u8 pad_1to7 : 7;
} PanelFlags99;

extern void func_ov013_02071094(void);
extern void func_ov013_020711f8(void);
extern void func_ov013_02070b1c(void);
extern void func_ov013_02070b78(int a, int b);
extern int data_ov013_02074ce0;

/* Dispatches three pending panel actions from flag bits. */
void func_ov013_0206c9d4(void) {
    if (((PanelFlags98 *)(data_ov013_02074ce0 + 0x98))->doFirst) {
        func_ov013_02071094();
    }
    if (((PanelFlags99 *)(data_ov013_02074ce0 + 0x99))->doSecond) {
        func_ov013_020711f8();
    }
    if (((PanelFlags98 *)(data_ov013_02074ce0 + 0x98))->doThird) {
        func_ov013_02070b1c();
    }
    if (!((PanelFlags98 *)(data_ov013_02074ce0 + 0x98))->doAction) {
        return;
    }
    func_ov013_02070b78(*(s8 *)(data_ov013_02074ce0 + 0x2f0) + 1, *(s8 *)(data_ov013_02074ce0 + 0x2ec));
    {
        int flags = *(u8 *)(data_ov013_02074ce0 + 0x98);
        flags = flags & ~2;
        *(u8 *)(data_ov013_02074ce0 + 0x98) = (u8)flags;
    }
}
