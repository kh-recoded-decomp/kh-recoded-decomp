#include "nitro/types.h"

extern void func_02000b64(u32 addr);
extern void CARD_CheckEnabled(void);
extern u32 func_02009278(void);
extern void func_02004cf0(void);
extern BOOL func_020093d0(u32 *request, int setArgs, u32 arg1, u32 arg2);
extern u32 data_02056fe0;

void func_020099d4(u32 mask, u32 arg1, u32 arg2) {
    u32 allowed;

    func_02000b64(0x2000bac);
    CARD_CheckEnabled();
    allowed = func_02009278();
    if (mask != (allowed & mask)) {
        func_02004cf0();
    }
    func_020093d0(&data_02056fe0, 1, arg1, arg2);
}
