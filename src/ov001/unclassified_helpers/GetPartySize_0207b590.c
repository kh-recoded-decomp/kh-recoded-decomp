#include "nitro/types.h"

typedef struct {
    u8 pad[4];
    u16 memberIds[3];
} Party;

extern Party *func_020505a8(void);
extern u32 func_ov001_0207b3cc(void);
extern u32 func_ov001_0207b5e8(void);
extern int func_ov025_020b6310(void);

int GetPartySize_0207b590(void) {
    Party *party = func_020505a8();
    int i;
    if (func_ov001_0207b3cc() == 2 && func_ov001_0207b5e8() != 0) {
        return func_ov025_020b6310();
    }
    for (i = 0; i < 3; i++) {
        if (party->memberIds[i] == 0xffff) {
            break;
        }
    }
    return i + 1;
}
