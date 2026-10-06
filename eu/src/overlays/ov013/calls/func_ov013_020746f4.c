#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void PlaySoundEffect(int value, int flag);

void func_ov013_020746f4(void) {
    *(u8 *)(data_ov013_02074ce0 + 3) = 2;
    PlaySoundEffect(2, 1);
}
